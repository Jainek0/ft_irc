
#include "../header/irc.hpp"

Client::Client()
{}

Client::Client(int fd, std::string nick, std::string username)
    : _fd(fd), _nick(nick), _username(username)
{}

Client::Client(const Client &other)
{
    *this = other;
}

Client& Client::operator=(const Client &other)
{
    if (this != &other)
    {
        _fd = other._fd;
        _nick = other._nick;
        _username = other._username;
    }
    return *this;
}

Client::~Client()
{}
