
#include "../_header/irc.hpp"

Cmd::~Cmd()
{}

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
    if (!_prefix.empty())
        std::cout << "<CMD:" << _prefix << "\n\t" << _command;
    else
        std::cout << "<CMD\n\t" << _command;
    for (size_t i = 0; i < _args.size(); i++)
        std::cout << "\n\t" << _args[i];
    std::cout << "\n>"<< std::endl;
}

Cmd::Cmd(const Cmd& other)
    : _prefix(other._prefix), _command(other._command), _args(other._args)
{}

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

const std::string& Cmd::prefix() const {return _prefix;}

const std::string& Cmd::command() const {return _command;}

const std::vector<std::string> & Cmd::args() const {return _args;}

size_t Cmd::sizeArgs() const { return _args.size();}

const std::string& Cmd::arg(size_t i) const
{
    static const std::string empty;

    if (i >= _args.size())
        return empty;
    return _args[i];
}


const std::string Cmd::argcs(size_t i) const
{
    std::string cs;

    if (i >= _args.size())
        return NULL;
    while (i >= _args.size())
        cs += _args[i++];
    return cs;
}