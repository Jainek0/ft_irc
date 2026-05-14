

#ifndef TOSTRING_HPP
#define TOSTRING_HPP

#include "../_header/irc.hpp"

template <typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif