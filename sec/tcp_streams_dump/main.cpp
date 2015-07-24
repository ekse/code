#include <iostream>

#include <tins/tins.h>

/*
 * This is a project to test the libtins library
 *
 */

using namespace std;


class TcpStreamsDumper {
public:
    unsigned int get_packet_count() const {
        return packet_count_;
    }

    void process(Tins::FileSniffer &pcap) {
        pcap.sniff_loop(std::bind(&TcpStreamsDumper::packet_callback, this, std::placeholders::_1));
    }


private:
    unsigned int packet_count_ = 0;

    bool packet_callback(const Tins::PDU &pdu) {
        packet_count_ += 1;
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

    // reads the TCP streams
    TcpStreamsDumper dumper{};
    dumper.process(pcap);

    cout << dumper.get_packet_count() << " packets" << endl;


    // write server data to files

    return 0;
}