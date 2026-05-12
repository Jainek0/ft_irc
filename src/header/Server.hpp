
#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server
{
	public:
		Server(int pid, std::string password);
		Server(Server &other);
		Server& operator=(const Server &other);
		~Server();

		void acceptClient();
		void removeClient(int fd);
		void handleCommand(int fd, std::string cmd);
			
	private:
		int 		_pid;
		std::string	_pasword;
		std::map<int,Client> _clients;
		std::map<std::string, Channel> _channels;
};

#endif