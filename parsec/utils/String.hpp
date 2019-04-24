#ifndef PARSEC_STRING_H
#define PARSEC_STRING_H
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

void split(const std::string &text, std::vector<std::string>& lines, const char sep) {
  std::size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != std::string::npos) {
    lines.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  lines.push_back(text.substr(start));
}

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

template <> std::string to_string( const double& n )
{
    std::ostringstream stm ;
    stm << std::setprecision(10) << n;
    return stm.str() ;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
#endif // PARSEC_STRING_H
