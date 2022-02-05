#include <iostream>
#include <string>

#include "../../include/UdpSocket.h"
#include "../../include/aes.hpp"
#include "../read_single_conf.h"

using std::cout;
using std::endl;
using std::string;

using toolbox::UdpSocket;

string fetch_ip()
{
    FILE *fp;
    char path[10000];

    fp = popen("curl -s ifconfig.me", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n" );
        exit(1);
    }

    string output = "";
    while ( fgets(path, sizeof( path ), fp ) != NULL )
    {
        output += path;
    }

    /* close */
    pclose(fp);
    return output;
}



int main( int argc, char *argv[] )
{
    string server_ip = read_single_conf( "/home/noxx/.config/lacus/target/ip" );
    string server_port = read_single_conf( "/home/noxx/.config/lacus/target/port" );
    string secret = read_single_conf( "/home/noxx/.config/lacus/target/key" );

    if(secret == "")\
        return 10;

    int pid = fork();

    if( pid < 0 )
    {
        return 271;
    }
    else if ( pid == 0 )
    {
        int curl_exit_code = execl("$1 > /dev/null 2>&1\n"
                                   "status=$?\n"
                                   "echo ${status}\n"
                                   "exit ${status}", "--version", NULL );

        if( curl_exit_code == -1 )
            return 270;

        cout << "curl exit code is: " << curl_exit_code << endl;
    }

    string my_ip = fetch_ip();
    cout << my_ip << endl;
    UdpSocket sock = UdpSocket();
    sock.udp_create();

    std::vector<uint8_t> secret_vec(secret.begin(), secret.end());
        uint8_t * key = &secret_vec[0];

    std::vector<uint8_t> ip_vec(my_ip.begin(), my_ip.end());
        uint8_t * in = &ip_vec[0];

    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

    struct AES_ctx ctx;

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, in, strlen((char*)in));

    sock.udp_send((char*)in, server_ip, server_port );

    sock.close();
    return 0;
}
