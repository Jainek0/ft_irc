
#include "../_header/irc.hpp"

std::vector<std::string> split(const std::string& str, char sep)
{
    std::vector<std::string> result;
    std::string token;
    std::istringstream iss(str);

    while (std::getline(iss, token, sep))
    {
        if (!token.empty())
            result.push_back(token);
    }
    return result;
}