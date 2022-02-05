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

#include "toolbox.h"

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;

/**
 * todo: make delemiter as str
 * @param str
 * @param delemiter
 * @param num
 * @return
 */
vector <string> toolbox::str::split(std::string str, char delemiter, int num )
{
    vector <std::string> split_str;
    std::string tmp = "";

    if( num < -1 )
    {
        num = -1;
    }

    unsigned int num_count = 0;

    for ( int i = 0; i < str.size() + 1; i++ )
    {
        if( num_count < num && str[i] == delemiter && tmp != "" || i == str.size())
        {
            split_str.push_back( tmp );
            tmp = "";
            num_count++;
        }
        else if( str[i] != delemiter || num_count >= num )
        {
            tmp += str[i];
        }

    }
    return split_str;
}

/**
 *
 * @param str
 * @param from
 * @param to
 * @return
 */
std::string toolbox::str::replace(std::string str, const std::string &from, const std::string &to )
{
    size_t start_pos = 0;
    while (( start_pos = str.find( from, start_pos )) != std::string::npos )
    {
        str.replace( start_pos, from.length(), to );
        start_pos += to.length(); // Handles case where 'to' infile a substring of 'from'
    }
    return str;
}

/**
 *
 * @param file_path
 * @return
 */
bool toolbox::fs::file_exists( const std::string & file_path )
{
    ifstream f( file_path.c_str() );
    return f.good();
}

/**
 *
 * @param src
 * @param dest
 * @return
 */
void toolbox::str::const_char_ptr_to_char_ptr(char *src, char *dest )
{
    dest = new char[strlen(src)+1];
    while (( *dest = *src) != '\0' )
    {
        dest += 1;
        src += 1;
    }
}

/**
 *
 * @param dir_path
 * @return
 */
vector <string> toolbox::fs::get_files_in_dir( std::string dir_path, bool file_name )
{
    vector <std::string> file_paths;

    for ( auto &p: std::experimental::filesystem::directory_iterator( dir_path ))
        if( !file_name )
            file_paths.push_back( p.path());
        else
            file_paths.push_back( std::filesystem::path( p.path()).filename() );

    std::sort( file_paths.begin(), file_paths.end() );
    return file_paths;
}

/**
 *
 * @param dir_path
 * @return
 */
int toolbox::fs::get_num_files( std::string dir_path )
{
    int num_files = 0;

    for ( auto &p: std::experimental::filesystem::directory_iterator( dir_path ))
        num_files++;

    return num_files;
}

/**
 *
 */
void toolbox::fs::set_lock( const std::string & id )
{
    std::string str_cmd = "touch " + id + ".lock";
    system( str_cmd.c_str() );
}

/**
 *
 */
void toolbox::fs::release_lock( const std::string & id )
{
    std::string str_cmd = "rm " + id + ".lock";
    system( str_cmd.c_str() );
}

/**
 *
 * @param id
 * @return
 */
bool toolbox::fs::file_locked( const std::string & id )
{
    return file_exists( id + ".lock" );
}

/**
 *
 * @param date
 * @return
 */
time_t toolbox::dt::stot(const std::string &date, const std::string &format )
{
    const char *time_details = date.c_str();
    time_t result = 0;
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
    std::string num_format = toolbox::dt::dftnf(format );

    if( sscanf( time_details, num_format.c_str(), &year, &month, &day, &hour, &min, &sec ))
    {
        struct tm breakdown = { 0 };
        breakdown.tm_year = year - 1900; /* years since 1900 */
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = hour;
        breakdown.tm_min = min;
        breakdown.tm_sec = sec;
        breakdown.tm_isdst = 1;

        if(( result = mktime( &breakdown )) == ( time_t ) - 1 )
        {
            cerr << "toolbox::dt::stot() - Could not convert time input to time_t: " << stderr << endl;
            return EXIT_FAILURE; // todo exception
        }
    }

    return result;
}

/**
 *
 * @param date
 * @return
 */
std::string toolbox::dt::ttos(const time_t &date, const std::string &format )
{
    const char *c_format = format.c_str();
    std::tm *ptm = std::localtime( &date );
    char buffer[100];
    std::strftime( buffer, 100, c_format, ptm );
    std::string oString( buffer );
    return oString;
}

/**
 *
 * @param date_format
 * @return
 */
std::string toolbox::dt::dftnf(std::string date_format )
{
    std::string tmp = date_format;
    tmp = toolbox::str::replace(tmp, "%Y", "%4d" );
    tmp = toolbox::str::replace(tmp, "%m", "%2d" );
    tmp = toolbox::str::replace(tmp, "%d", "%2d" );
    tmp = toolbox::str::replace(tmp, "%H", "%2d" );
    tmp = toolbox::str::replace(tmp, "%M", "%2d" );
    tmp = toolbox::str::replace(tmp, "%S", "%2d" );
    return tmp;
}

/**
 *
 * @param t
 * @param se
 * @return
 */
time_t toolbox::dt::add_se(const time_t &t, const int &se )
{
    struct tm *tm = localtime( &t );
    tm->tm_sec += se;
    return mktime( tm );
}

/**
 *
 * @param t
 * @param mi
 * @return
 */
time_t toolbox::dt::add_mi(const time_t &t, const int &mi )
{
    struct tm *tm = localtime( &t );
    tm->tm_min += mi;
    return mktime( tm );
}

/**
 *
 * @param t
 * @param hr
 * @return
 */
time_t toolbox::dt::add_hr(const time_t &t, const int &hr )
{
    struct tm *tm = localtime( &t );
    tm->tm_hour += hr;
    return mktime( tm );
}

/**
 *
 * @param t
 * @param da
 * @return
 */
time_t toolbox::dt::add_da(const time_t &t, const int &da )
{
    struct tm *tm = localtime( &t );
    tm->tm_mday += da;
    return mktime( tm );
}

/**
 *
 * @param t
 * @param wk
 * @return
 */
time_t toolbox::dt::add_wk(const time_t &t, const int &wk )
{
    struct tm *tm = localtime( &t );
    tm->tm_wday += wk;
    return mktime( tm );
}

/**
 *
 * @param t
 * @param mo
 * @return
 */
time_t toolbox::dt::add_mo(const time_t &t, const int &mo )
{
    struct tm *tm = localtime( &t );
    tm->tm_mon += mo;
    return mktime( tm );
}

/**
 *
 * @param t
 * @param yr
 * @return
 */
time_t toolbox::dt::add_yr(const time_t &t, const int &yr )
{
    struct tm *tm = localtime( &t );
    tm->tm_year += yr;
    return mktime( tm );
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_se(const time_t &end, const time_t &start )
{
    return difftime( end, start );
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_mi(const time_t &end, const time_t &start )
{
    int s = difftime( end, start );
    return s / 60;
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_hr(const time_t &end, const time_t &start )
{
    int s = difftime( end, start );
    return s / 3600;
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_da(const time_t &end, const time_t &start )
{
    int s = difftime( end, start );
    return s / 86400;
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_wk(const time_t &end, const time_t &start )
{
    int s = difftime( end, start );
    return s / 604800;
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_mo(const time_t &end, const time_t &start )
{
    int s = difftime( end, start );
    return s / 86400; // todo
}

/**
 *
 * @param end
 * @param start
 * @return
 */
double toolbox::dt::diff_yr(const time_t &end, const time_t &start )
{
    int s = difftime( end, start );
    return s / 86400; // todo
}

/**
 *
 * @return
 */
std::string toolbox::rnd::get_uuid()
{
    static std::random_device dev;
    static std::mt19937 rng( dev());

    std::uniform_int_distribution<int> dist( 0, 15 );

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for ( int i = 0; i < 16; i++ )
    {
        if( dash[i] )
        { res += "-"; }
        res += v[dist( rng )];
        res += v[dist( rng )];
    }
    const std::string const_res = res;
    return const_res;
}