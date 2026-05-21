
#ifndef CMD_HPP
# define CMD_HPP

# include "irc.hpp"

class Cmd
{
    public:
        Cmd(std::string& str);
        Cmd(Cmd& other);
        Cmd& operator=(const Cmd& other);
        ~Cmd();

        std::string                 _prefix;
        std::string                 _command;
        std::vector<std::string>    _args;

    private:
        void rec_trailing(std::istringstream& ss, std::string& token);
};

#endif