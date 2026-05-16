
#include "../_header/irc.hpp"

Client::Client(int fd)
    : _fd(fd)
{}

Client::Client(const Client &other)
    : _fd(other._fd), _userName(other._userName), _nickName(other._nickName)
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


const std::string Client::getNickName() const { return _nickName; }

const std::string Client::getUserName() const { return _userName; }
const std::string Client::getPrefix() const { return (":" + _nickName + "@" + _userName); }


int Client::getFd() const { return _fd; }

void Client::setNickName(const std::string nickName) { _nickName = nickName; }

void Client::setUserName(const std::string username) { _userName = username; }
