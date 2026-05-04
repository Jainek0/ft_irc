
#ifndef SERVER_HPP
#define SERVER_HPP

#include "header/irc.hpp"

class Server
{
	public:
		Server(size_t pid, std::string password);
		Server(Server &other);
		Server& operator=(Server &other);
		~Server();

		void acceptClient();
		void removeClient(int fd);
		void handleCommand(int fd, std::string cmd);
			
	private:
		size_t 		_pid;
		std::string	_pasword;
		// std::map<int,Client> _clients;
		// std::map<std::string,Channel> _channels;

};

#endif