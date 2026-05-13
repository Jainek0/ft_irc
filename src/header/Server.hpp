
#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server
{
	public:
		Server();
		Server(int pid, std::string password);
		Server(const Server &other);
		Server& operator=(const Server &other);
		~Server();

		void acceptClient(int pid);
		void removeClient(std::string nickUser);
		void handleCommand(int pid, std::string cmd);
			
	private:
		int 													_pid;
		std::string												_pasword;
		std::map<int, Client> 									_clients;
		std::map<std::string, Channel> 							_channels;
		std::map<std::string, void (Server::*)(Client&, Cmd&)> 	_commands;

		/*  ------------------< commands >------------------*/

		std::map<std::string, void (Server::*)(Client&, Cmd&)> createCommands();
		void kick(Client& user, Cmd& cmd);
		void join(Client& user, Cmd& cmd);

};

#endif