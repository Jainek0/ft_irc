
#include "../header/irc.hpp"

Client::Client(int fd, std::string nick, std::string username)
    : _fd(fd), _nick(nick), _username(username)
{}

Client::Client(const Client &other)
    : _fd(other._fd), _nick(other._nick), _username(other._username)
{}

// Client& Client::operator=(const Client &other)
// {
//     if (this != &other)
//     {
//         _username = other._username;
//     }
//     return *this;
// }

Client::~Client()
{}


const std::string Client::getUsername() const { return _username; }

const std::string Client::nick() const { return _nick; }

int Client::fd() const { return _fd; }

void Client::setUsername(const std::string username) { _username = username; }
