#ifndef TOSIZE_T_HPP
# define TOSIZE_T_HPP

# include "../_header/irc.hpp"


size_t toSize_t(const std::string& str)
{
    size_t result = 0;

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] < '0' || str[i] > '9')
            throw std::invalid_argument("Invalid number");

        result = result * 10 + (str[i] - '0');
    }

    return result;
}

#endif