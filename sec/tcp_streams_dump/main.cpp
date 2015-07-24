#include <iostream>

#include <tins/tins.h>

/*
 * This is a project to test the libtins library
 *
 */

using namespace std;


class PacketParser {
public:
    unsigned int get_packet_count() const {
        return packet_count_;
    }

    void process(Tins::FileSniffer& pcap) {
        pcap.sniff_loop(std::bind(&PacketParser::packet_callback, this, std::placeholders::_1));
    }


private:
    unsigned int packet_count_ = 0;

    bool packet_callback(const Tins::PDU& pdu) {
        packet_count_ += 1;
        return true;
    }
};


class TcpStreamsDumper {
public:

    TcpStreamsDumper() {
        streams_follower_ = Tins::TCPStreamFollower();
    }

    unsigned int streams_count() const {
        return streams_count_;
    }


    void process(Tins::BaseSniffer& sniffer) {
        streams_follower_.follow_streams(sniffer,
                                         std::bind(&TcpStreamsDumper::data_stream_callback, this, std::placeholders::_1),
                                         std::bind(&TcpStreamsDumper::end_stream_callback, this,  std::placeholders::_1)
        );
    }

private:
    Tins::TCPStreamFollower streams_follower_;
    unsigned int streams_count_ = 0;

    bool data_stream_callback(const Tins::TCPStream& stream) {
        //cout << "[trace] in data_stream_callback()" << endl;
        return true;
    }

    // write server data to files
    bool end_stream_callback(const Tins::TCPStream& stream) {
        //cout << "[trace] in end_stream_callback()" << endl;
        streams_count_ += 1;

        cout << "Stream: " << stream.stream_info().client_addr << ":" << stream.stream_info().client_port << " --> ";
        cout << stream.stream_info().server_addr << ":" << stream.stream_info().server_port;
        cout << " Server payload: " << stream.server_payload().size() << " bytes" << endl;

        string payload(stream.server_payload().cbegin(), stream.server_payload().cend());
        cout << "Content: " << endl;
        cout << payload << endl << endl;

        return true;
    }
};


int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "usage : tcp_streams_dump <filename>" << endl;
        exit(0);
    }

    // open pcap file
    Tins::FileSniffer pcap{argv[1]};

    // count the packets
    PacketParser packet_parser{};
    packet_parser.process(pcap);

    cout << packet_parser.get_packet_count() << " packets" << endl;

    // read the TCP streams
    Tins::FileSniffer pcap2{argv[1]};
    TcpStreamsDumper streams_dumper{};
    streams_dumper.process(pcap2);

    cout << "Processed " << streams_dumper.streams_count() << " streams" << endl;



    return 0;
}