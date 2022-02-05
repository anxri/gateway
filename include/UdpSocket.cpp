/*
 * Copyright (c) 2022 Noxx
 *
 * Copyright 2021 Dejan Horavkovic
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and
 * this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS
 * PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "UdpSocket.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

/**
 *
 * @return
 */
bool toolbox::UdpSocket::udp_create()
{
    m_sock = socket( AF_INET, SOCK_DGRAM, 0 );

    if( m_sock < 0 )
    {
        cerr << "udp_create :: " << strerror( errno ) << endl;
        return false;
    }

    cout << "UDP socket created." << endl;
    return true;
}

/**
 *
 * @param addr
 * @param msg
 * @param port
 * @return
 */
bool toolbox::UdpSocket::udp_send( string msg, string addr, string port ) const
{
    const char *ch_addr     = addr.c_str();
    const char *ch_msg      = msg.c_str();
    int i_port              = stoi( port );

    struct sockaddr_in addr_target;
    struct hostent *h;

    int status;

    h = gethostbyname( ch_addr );

    if( h == NULL )
        cout << "Unknown Host." << endl;

    addr_target.sin_family = h->h_addrtype;

    memcpy( (char *) &addr_target.sin_addr.s_addr, h->h_addr_list[0], h->h_length );

    addr_target.sin_port = htons( i_port );

    status = ::sendto(
            m_sock,
            ch_msg,
            strlen(ch_msg ),
            0,
            (struct sockaddr *) &addr_target,
            sizeof( addr_target ));

    if( status < 0 )
    {
        cerr << "udp_send :: " << strerror( errno ) << endl;
        return false;
    }

    return true;
}

/**
 *
 * @param s
 * @return
 */
int toolbox::UdpSocket::udp_recv( string & recv_str ) const
{
    struct sockaddr_in addr_recvform;

    int len, status;

    char buf[MAXLINE + 1];

    memset( buf, 0, MAXLINE + 1 );

    len = sizeof( addr_recvform );

    char * str;

    status = recvfrom(
            m_sock,
            buf,
            MAXLINE,
            0,
            (struct sockaddr *) &addr_recvform,
            ( socklen_t * ) & len );

    if( status < 0 )
    {
        cerr << "udp_recv :: " << strerror( errno ) << endl;
        return false;
    }

    recv_str = buf;
    return status;
}
