#include <iostream>
#include <fstream>

#include <tins/tins.h>

/*
 * This is a toy program that writes TCP streams to a files using the libtins library.
 * https://github.com/mfontanini/libtins
 */

bool write_string_to_file(const std::string &output_filename, const std::string &data) {

    std::ofstream outfile(output_filename);

    std::cout << "writing to file " << output_filename << std::endl;
    if (!outfile.is_open()) {
        std::cout << "[error] couldn't write to " << output_filename << " exiting.";
        exit(-1);
    }

    outfile << data;
    outfile.close();
    return true;
}

using namespace std;


class TcpStreamsDumper {
public:

    TcpStreamsDumper() {
        streams_follower_ = Tins::TCPStreamFollower();
    }

    unsigned int streams_count() const {
        return streams_count_;
    }


    void process(Tins::BaseSniffer &sniffer) {
        streams_follower_.follow_streams(sniffer,
                                         std::bind(&TcpStreamsDumper::data_stream_callback, this,
                                                   std::placeholders::_1),
                                         std::bind(&TcpStreamsDumper::end_stream_callback, this, std::placeholders::_1)
        );
    }

private:
    Tins::TCPStreamFollower streams_follower_;
    unsigned int streams_count_ = 0;

    bool data_stream_callback(const Tins::TCPStream &stream) {
        return true;
    }

    // write server data to files
    bool end_stream_callback(const Tins::TCPStream &stream) {
        streams_count_ += 1;

        const auto &stream_info = stream.stream_info();

        cout << "Stream: " << stream.id() << " ";
        cout << stream_info.client_addr << ":" << stream_info.client_port << " --> ";
        cout << stream_info.server_addr << ":" << stream_info.server_port << endl;
        cout << "Client payload: " << stream.client_payload().size() << " bytes, ";

        const string client_payload(stream.client_payload().cbegin(), stream.client_payload().cend());
        std::ostringstream o_client;
        o_client << "streams/client/" << stream.id() << ".bin";
        string output_filename = o_client.str();
        write_string_to_file(output_filename, client_payload);


        cout << "Server payload: " << stream.server_payload().size() << " bytes, ";
        const string server_payload(stream.server_payload().cbegin(), stream.server_payload().cend());
        std::ostringstream o_server;
        o_server << "streams/server/" << stream.id() << ".bin";
        output_filename = o_server.str();
        write_string_to_file(output_filename, server_payload);
        std::cout << endl;

        return true;
    }
};


int main(int argc, char **argv) {

    if (argc != 2) {
        cout << "usage : tcp_streams_dump <filename>" << endl;
        exit(0);
    }

    // open pcap file
    Tins::FileSniffer pcap{argv[1]};

    // read the TCP streams
    TcpStreamsDumper streams_dumper{};
    streams_dumper.process(pcap);

    cout << "Processed " << streams_dumper.streams_count() << " streams" << endl;


    return 0;
}