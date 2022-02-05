//
// Created by noxx on 2/5/22.
//

#ifndef LACUS_READ_SINGLE_CONF_H
#define LACUS_READ_SINGLE_CONF_H

#include <string>
#include <iostream>
#include <fstream>


std::string read_single_conf(const std::string & path )
{
    std::string val;
    std::string line;
    std::fstream read_secret;
    read_secret.open( path, std::ios::in );
    if ( !read_secret )
    {
        std::cout << "LOOOL" << std::endl;
    } else {
        char ch;
        while (1)
        {
            read_secret >> ch;
            if (read_secret.eof())
                break;

            val += ch;
        }
    }
    read_secret.close();
    return val;
}

#endif
