#include <iostream>
#include <string>
#include <fstream>
#include <sys/prctl.h>

#include "../../include/UdpSocket.h"
#include "../../include/aes.hpp"
#include "../read_single_conf.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

using toolbox::UdpSocket;

void store_ip( const std::string ip )
{
    ofstream write_ip;
    write_ip.open( "/home/gateway/.config/lacus/ip" );
    write_ip << ip;
    write_ip.close();
}

int main( int argc, char *argv[] )
{
    string server_port = read_single_conf("/home/gateway/.config/lacus/server/port");
    string secret = read_single_conf("/home/gateway/.config/lacus/server/key");
    string recv;

    UdpSocket sock = UdpSocket();
    sock.udp_create();
    sock.bind( server_port );

    for(;;)
    {
        std::vector<uint8_t> secret_vec(secret.begin(), secret.end());
        uint8_t * key = &secret_vec[0];

        uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

        struct AES_ctx ctx;

        sock.udp_recv( recv );

        std::vector<uint8_t> recv_vec(recv.begin(), recv.end());
            uint8_t * in = &recv_vec[0];

        AES_init_ctx_iv(&ctx, key, iv);
        AES_CTR_xcrypt_buffer(&ctx, in, strlen((char*)in));

        std::string ip = (char*)in;
        cout << "writing ip to disk. " << ip << endl;
        store_ip( ip );

    }

    return 0;
}
