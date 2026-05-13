
#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server
{
	public:
		Server(int fd, std::string password);
		Server(const Server &other);
		~Server();

		void 	acceptClient(const int fd);
		void 	removeClient(const int fd);
		void 	acceptClient(const std::string fd);
		void 	removeClient(const std::string fd);
		void 	handleCommand(Client& user, std::string str);
		
		void	putMsg(Client target, std::string msg)	const;
		
		bool 	checkClient(const std::string fd) 		const;
		bool 	checkClient(const int fd) 				const;
		Client&	findClient(const int fd);
		Client&	findClient(const std::string fd);


	private:
		const int												_fd;
		const std::string										_pasword;
		std::map<int, Client> 									_clientsFd;
		std::map<std::string, Client> 							_clientsNick;
		std::map<std::string, Channel> 							_channels;
		std::map<std::string, void (Server::*)(Client&, Cmd&)> 	_commands;

	/*  ------------------< commands >------------------*/

		std::map<std::string, void (Server::*)(Client&, Cmd&)> createCommands();
		void join(Client& user, Cmd& cmd);
		void kick(Client& user, Cmd& cmd);
		void mode(Client& user, Cmd& cmd);
		void topic(Client& user, Cmd& cmd);

	/*
	NICK → pseudo
	USER → username/login

	PRIVMSG → message privé / channel
	PING → keepalive
	QUIT → déconnexion

	PASS → mot de passe du serveur
	PART → déconnexion du channel
	INVITE → invite channel



		*/
	// [
	// 	∗ KICK - Eject a client from the channel
	// 	∗ INVITE - Invite a client to a channel
	// 	∗ TOPIC - Change or view the channel topic
	// 	∗ MODE - Change the channel’s mode:
	// 		· i: Set/remove Invite-only channel
	// 		· t: Set/remove the restrictions of the TOPIC command to channel
	// 		operators
	// 		· k: Set/remove the channel key (password)
	// 		· o: Give/take channel operator privilege
	// 		· l: Set/remove the user limit to channel
	// ]

	/*  ------------------< ban >------------------*/

		Server& operator=(const Server &other);

};

#endif