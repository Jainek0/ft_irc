
#include "../header/irc.hpp"

Client::Client(int fd) : _fd(fd)
{}

Client::Client(Client &other)
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
        _authenticated = other._authenticated;
    }
    return *this;
}

Client::~Client()
{}
