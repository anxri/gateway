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

#include "Socket.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::stoi;
using toolbox::str::const_char_ptr_to_char_ptr;

/**
 *
 */
Socket::Socket() : m_sock( 0 )
{
    //
}

/**
 *
 * @param obj
 */
Socket::Socket( const Socket &obj )
{
    m_sock = obj.m_sock;
    m_addr = obj.m_addr;
}

/**
 *
 */
Socket::~Socket()
{
    close();
}

void Socket::set_socket( const int & sock )
{
    m_sock = sock;
}

int Socket::get_socket()
{
    return m_sock;
}

bool Socket::infile_valid() const
{
    return m_sock != -1;
}

/**
 *
 * @param port
 * @return
 */
bool Socket::bind( const string &port, int in_addr )
{
    unsigned int i_port = stoi( port );

    if( !infile_valid() )
        return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(in_addr );
    m_addr.sin_port = htons( i_port );

    // Bind the socket with the server address
    int bind_return = ::bind( m_sock, (struct sockaddr *) &m_addr, sizeof( m_addr ));

    if( bind_return == -1 )
    {
        cerr << "udp_recv :: " << strerror( errno ) << endl;
        return false;
    }

    cout << "Socket binded." << endl;
    return true;
}

/**
 *
 * @return
 */
int Socket::close() const
{
    if( infile_valid() )
        ::close(m_sock );

    return cleanup();
}

/**
 *
 * @return
 */
int Socket::cleanup() const
{
    return shutdown(m_sock, SHUT_RDWR );
}
