#ifndef PARSEC_STRING_H
#define PARSEC_STRING_H
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

void split(const std::string &text, std::vector<std::string>& lines, char sep);

std::string replaceAll(std::string str, const std::string& from, const std::string& to);

/*
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}*/

std::string to_string(const int& n);

std::string to_string(const double& n);

#endif // PARSEC_STRING_H
