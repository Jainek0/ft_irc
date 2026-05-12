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

		int 			fd;
		std::string 	nick;
		std::string 	username;
		bool 			authenticated;
};

#endif