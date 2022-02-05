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

#include "Log.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

using namespace toolbox;
using ::fs::file_exists;

/**
 *
 * @param t
 * @return
 */
std::string toolbox::Log::get_type_string( type t )
{
    switch ( t )
    {
        case FATAL:     return "FATAL";
        case ERROR:     return "ERROR";
        case WARN:      return "WARN";
        case INFO:      return "INFO";
        case DEBUG:     return "DEBUG";
        case TRACE:     return "TRACE";
    }
}

/**
 *
 * @param t
 * @param msg
 * @param print
 */
void toolbox::Log::log_internal( toolbox::Log::type t, const std::string & msg, print print )
{
    std::time_t time = std::time( nullptr );
    auto tm = *std::localtime(& time );

    string current_time     = toolbox::dt::ttos(time, "%d-%m-%Y %H-%M-%S" );
    string out              = "[" + get_type_string( t ) + "] - " + current_time + " | " + msg;

    if(( m_global_print_mode && print == DEFAULT ) || print == PRINT )
        cout << out << endl;

    ofstream log_file;
    log_file.open ( m_file_path );
    log_file << out;
    log_file.close();
}

toolbox::Log::Log( const std::string & file_path, bool global_print_mode )
{
    m_file_path             = file_path;
    m_global_print_mode     = global_print_mode;
}

void toolbox::Log::fatal( const string & msg, print print )
{
    log_internal( FATAL, msg, print );
}

void toolbox::Log::error( const string & msg, print print )
{
    log_internal( ERROR, msg, print );
}

void toolbox::Log::warn( const std::string & msg, print print )
{
    log_internal( WARN, msg, print );
}

void toolbox::Log::info( const std::string & msg, print print )
{
    log_internal( INFO, msg, print );
}

void toolbox::Log::debug( const std::string & msg, print print )
{
    log_internal( DEBUG, msg, print );
}

void toolbox::Log::trace( const std::string & msg, print print )
{
    log_internal( TRACE, msg, print );
}