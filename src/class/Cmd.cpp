
#include "../_header/irc.hpp"

Cmd::Cmd(std::string& str)
{
    std::istringstream  ss(str);
    std::string         token;

    if (str[0] == ':')
        ss.seekg(1) >> _prefix;
    ss >> _command;
    while (ss >> token)
    {
        if (token[0] == ':')
        {
            std::string trailing = token + " ";
            trailing.erase(0,1);
            while (ss >> token)
                trailing += token + " ";
            _args.push_back(trailing);
            break;
        }
        _args.push_back(token);
    }
    std::cout << "<CMD " << _prefix << ">\n\t" << _command;
    for (size_t i = 0; i < _args.size(); i++)
        std::cout << "\n\t" << _args[i];
    std::cout << std::endl;
}

Cmd::Cmd(Cmd& other)
{
    *this = other;
}

Cmd& Cmd::operator=(const Cmd& other)
{
    if (this != &other)
    {
        _prefix = other._prefix;
        _command = other._command;
        _args = other._args;
    }
    return *this;
}

Cmd::~Cmd()
{}

