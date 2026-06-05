#include "../_header/irc.hpp"


// mapCommand_t Command::createCommands()
// {
// 	mapCommand_t commands;

// 	// commands["KICK"] = &Command::kick;
// 	// commands["JOIN"] = &Command::join;
// 	// commands["MODE"] = &Command::mode;
// 	// commands["TOPIC"] = &Command::topic;
// 	commands[""] = &Command::nickname;
// 	commands[""] = &Command::username;
// 	commands[""] = &Command::password;

// 	return commands;
// }

// void Command::handleCommand(Client& user, std::string str)
// {
// 	static mapCommand_t commands = createCommands();
// 	Server& serv = Server::getInstance();

// 	Cmd cmd(str);
// 	mapCommand_t::iterator itCmd(commands.find(cmd.command()));

// 	if (itCmd != commands.end())
// 		(itCmd->second)(user, cmd);
// 	else
// 		serv.putMsg(user, ERR_UNKNOWNCOMMAND(cmd.command()));
// }

void	Command::nickname(Client &user)
{
	char	buffer[1000];//size?

	send(user.getFd(), "nickname: \n", 11, SOCK_NONBLOCK);
	recv(user.getFd(), buffer, sizeof(buffer), SOCK_NONBLOCK);//loop gnl?

	std::map<int, Client>::iterator it;
	it = ((Server::getInstance()).getMapClientsFd()).find(user.getFd());
	it->second.setNickname(buffer);
	if(user.getNickname() != "")
	{
		((Server::getInstance()).getMapClientsNick()).erase(user.getNickname());
	}
	((Server::getInstance()).getMapClientsNick()).insert({buffer, Client(user.getFd(), buffer, user.getUsername())});
	user.setNickname(buffer);
}

void	Command::username(Client &user)
{
	char	buffer[1000];//size?

	send(user.getFd(), "username: \n", 11, SOCK_NONBLOCK);
	recv(user.getFd(), buffer, sizeof(buffer), SOCK_NONBLOCK);//loop gnl?

	std::map<int, Client>::iterator it;
	it = ((Server::getInstance()).getMapClientsFd()).find(user.getFd());
	it->second.setUsername(buffer);
	if (user.getNickname() != "")
	{
		std::map<std::string, Client>::iterator it2;
		it2 = ((Server::getInstance()).getMapClientsNick()).find(user.getNickname());
		it2->second.setUsername(buffer);
	}
	user.setUsername(buffer);
}

void	Command::password(Client &user)
{
	char	*buffer[1000];//size?

	if (!user.getNickname() || !user.getUsername())
	{
		send(user.getFd(), "Please first enter a nickname and a username\n", 45, O_NONBLOCK);
		return ;
	}
	else if (user.getAuthen() == TRUE)
	{
		send(user.getFd(), "Already logged in.\n", 19, O_NONBLOCK);
		return ;
	}
	send(user.getFd(), "password: \n", 11, O_NONBLOCK);
	recv(user.getFd(), buffer, buffsize, O_NONBLOCK);//loop gnl?
	if(buffer == (Server::getInstance()).getPassword())//strcmp()? char*/string
		user.setAuthen(TRUE);
}
