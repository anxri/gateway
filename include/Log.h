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
#ifndef TOOLBOX_LOG_H
#define TOOLBOX_LOG_H

#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

#include "toolbox.h"

namespace toolbox
{
    class Log
    {
        public:
            enum print
            {
                DEFAULT=0,
                PRINT=1,
                NO_PRINT=2
            };

        private:
            enum type
            {
                FATAL=0,
                ERROR=1,
                WARN=2,
                INFO=3,
                DEBUG=4,
                TRACE=5
            };

            std::string get_type_string( type t );

        protected:
            std::string m_file_path;            // where to save the Logger
            bool m_global_print_mode;           // true: print all, false print none

            void log_internal( type t, const std::string & msg, print print=DEFAULT );

        public:
            Log( const std::string & file_path, bool global_print_mode=false );

            void fatal( const std::string & msg, print print=DEFAULT );
            void error( const std::string & msg, print print=DEFAULT );
            void warn( const std::string & msg, print print=DEFAULT );
            void info( const std::string & msg, print print=DEFAULT );
            void debug( const std::string & msg, print print=DEFAULT );
            void trace( const std::string & msg, print print=DEFAULT );
    };
}

#endif
