
#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server
{
	public:
		Server(int pid, std::string password);
		Server(const Server &other);
		~Server();

		void 	acceptClient(const int pid);
		void 	removeClient(const int pid);
		void 	handleCommand(Client& user, std::string str);
		
		bool 	checkClient(const int pid) 	const;
		Client&	findClient(const int pid);

	
	private:
		const int												_pid;
		const std::string										_pasword;
		std::map<int, Client> 									_clients;
		std::map<std::string, Channel> 							_channels;
		std::map<std::string, void (Server::*)(Client&, Cmd&)> 	_commands;

	/*  ------------------< commands >------------------*/

		std::map<std::string, void (Server::*)(Client&, Cmd&)> createCommands();
		void kick(Client& user, Cmd& cmd);
		void join(Client& user, Cmd& cmd);

	/*  ------------------< ban >------------------*/

		Server& operator=(const Server &other);

};

#endif