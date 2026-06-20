#include "../_header/irc.hpp"

Client::Client(int fd, std::string ip)
	: _fd(fd), _ip(ip), _authenticated(0)
{}

Client::Client(const Client &other)
	: _fd(other._fd), _ip(other._ip) , _userName(other._userName), _nickName(other._nickName), _authenticated(0)
{}

// Client& Client::operator=(const Client &other)
// {
//     if (this != &other)
//     {
//         _username = other._username;
//     }
//     return *this;
// }

void Client::clearChannel()
{
	Server& serv = Server::getInstance();

	for (std::set<std::string>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (serv.findChannel(*it) != serv.endChannel())
		{
			serv.findChannel(*it)->second.rmUser(_fd);
			serv.findChannel(*it)->second.rmInvite(_fd);
		}
	}
}

Client::~Client()
{}


const std::string Client::getNickName() const { return _nickName; }

const std::string Client::getUserName() const { return _userName; }

const std::string Client::getPrefix() const { return (":" + _nickName + "!" + _userName + "@" + SERVER_HOST); }

int Client::getFd() const { return _fd; }

int Client::getAuthenti() const { return _authenticated; }

void Client::setAuthenti(int mod) { _authenticated = mod; }

void Client::setNickName(const std::string nickName) { _nickName = nickName; }

void Client::setUserName(const std::string username) { _userName = username; }

void Client::addChannel(const std::string channel) { _channels.insert(channel); }

void Client::rmChannel(const std::string channel) { _channels.erase(channel); }
