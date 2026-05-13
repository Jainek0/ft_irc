#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

class Client
{
	public:
		Client();
		Client(int fd, std::string nick, std::string username);
		Client(const Client &other);
		Client& operator=(const Client &other);
		~Client();

		int 			_fd;
		std::string 	_nick;
		std::string 	_username;
};

#endif