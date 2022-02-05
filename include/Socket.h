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

#ifndef SMARTHOME_SOCKET_H
#define SMARTHOME_SOCKET_H

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "toolbox.h"

const int MAXCONNECTIONS = 100;
const int MAXLINE = 999999;

class Socket
{
protected:

    int m_sock;

    sockaddr_in m_addr;

    char m_buffer[MAXLINE]; // find better solution and or make safe against stack overflows

public:
    Socket();

    Socket( const Socket &obj );

    virtual ~Socket();

    void set_socket( const int & sock );

    int get_socket();

    bool infile_valid() const;

    bool bind( const std::string &port, int in_addr=INADDR_ANY );

    int close() const;

    int cleanup() const;
};


#endif
