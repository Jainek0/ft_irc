#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

class Client
{
	public:
		Client(int fd);
		Client(Client &other);
		Client& operator=(const Client &other);
		~Client();

		int 			_fd;
		std::string 	_nick;
		std::string 	_username;
		bool 			_authenticated;
};

#endif