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

#include "TcpSocket.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

/**
 *
 * @return
 */
bool toolbox::TcpSocket::tcp_create()
{
    m_sock = ::socket( AF_INET, SOCK_STREAM, 0 );

    if( m_sock < 0 )
    {
        cerr << "tcp_create :: " << strerror( errno ) << endl;
        return false;
    }

    int y = 1; // todo garbage

    setsockopt( m_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &y, sizeof( y ));

    cout << "TCP socket created." << endl;

    return true;
}

/**
 *
 * @return
 */
bool toolbox::TcpSocket::tcp_listen() const
{
    if( !infile_valid() )
        return false;

    if( ::listen( m_sock, MAXCONNECTIONS ) == -1 )
    {
        cerr << "tcp_listen :: " << strerror( errno ) << endl;
        return false;
    }

    cout << "Socket listening." << endl;
    return true;
}

/**
 *
 * @param new_socket
 * @return
 */
bool toolbox::TcpSocket::tcp_accept( Socket & new_socket )
{
    int addr_length = sizeof( m_addr );
    new_socket.set_socket( ::accept( m_sock, ( struct sockaddr * ) NULL, NULL ));

    if( new_socket.get_socket() <= 0 )
    {
        cerr << "tcp_accept :: " << strerror( errno ) << endl;
        return false;
    }

    cout << "TCP connection accepted." << endl;
    return true;
}

/**
 *
 * @param host
 * @param port
 * @return
 */
bool toolbox::TcpSocket::tcp_connect( string host, string port )
{
    const char *ch_host = host.c_str();

    int i_port = stoi( port );

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons( i_port );

    // Convert IPv4 and IPv6 addresses from text to binary form
    if( inet_pton( AF_INET, ch_host, &m_addr.sin_addr ) <= 0 )
    {
        cerr << "tcp_connect :: " << strerror( errno ) << endl;
        return false;
    }

    if ( connect( m_sock, ( struct sockaddr * )&m_addr, sizeof( m_addr )) < 0 )
    {
        cerr << "tcp_connect :: " << strerror( errno ) << endl;
        return false;
    }

    cout << "TCP connection established." << endl;
    return true;
}

/**
 *
 * @param msg
 * @return
 */
bool toolbox::TcpSocket::tcp_send( string msg ) const
{
    const char *ch_msg = msg.c_str();
    if( ::send( m_sock, ch_msg, strlen( ch_msg ), 0 ) == -1 )
    {
        cerr << "tcp_send :: " << strerror( errno ) << endl;
        return false;
    }

    return true;
}

/**
 *
 * @param s
 * @return
 */
bool toolbox::TcpSocket::tcp_recv( string & recv_str ) const
{
    char buffer[MAXLINE + 1];
    memset( buffer, 0, sizeof( buffer ));
    int status = recv( m_sock, buffer, MAXLINE, 0 );

    if( status < 0 )
    {
        cerr << "tcp_recv :: " << strerror( errno ) << endl;
        return 0;
    }

    else if( status == 0 )
    {
        return false;
    }

    recv_str = string(& buffer[0], strlen( buffer ));
    return true;
}