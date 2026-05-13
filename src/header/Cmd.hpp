
#ifndef CMD_HPP
#define CMD_HPP

#include "irc.hpp"

class Cmd
{
    public:
        Cmd();
        Cmd(std::string& str);
        Cmd(const Cmd& other);
        Cmd& operator=(const Cmd& other);
        ~Cmd();

        std::string                 _prefix;
        std::string                 _command;
        std::vector<std::string>    _args;
};

#endif