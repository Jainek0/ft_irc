#include "../_header/irc.hpp"

mapCommand_t Command::createCommands()
{
    mapCommand_t commands;

    commands["KICK"] = &Command::fKick;
    commands["JOIN"] = &Command::fJoin;
    commands["MODE"] = &Command::fMode;
    commands["TOPIC"] = &Command::fTopic;
	commands["PRIVMSG"] = &Command::fPrivmsg;
    commands["PING"] = &Command::fPing;
    commands["QUIT"] = &Command::fQuit;
    commands["INVITE"] = &Command::fInvite;
	commands["USER"] = &Command::fUser;
    commands["NICK"] = &Command::fNick;

    return commands;
}



void Command::handleCommand(Client& user, std::string input)
{
    static mapCommand_t commands = createCommands();
    Server& serv = Server::getInstance();

	Cmd cmd(input);
	
	if (!(user.getAuthenti() == 2))
	{
		if (cmd.command() == "USER")
			fUser(user, cmd);
		else if (cmd.command() == "NICK")
			fNick(user, cmd);
		else if (cmd.command() == "PASS")
			fPass(user, cmd);
		else if (cmd.command() != "CAP" && cmd.command() != "0")
			serv.putMsg(user, "error no authenti");
	}
	else 
	{
		mapCommand_t::iterator itCmd(commands.find(cmd.command()));

		if (itCmd != commands.end())
			(itCmd->second)(user, cmd);
		else
			serv.putMsg(user, ERR_UNKNOWNCOMMAND(user.getNickName(), cmd.command()));
	}
}

/* ------------------------------------< commands >------------------------------------ */


void checkAuthenti(Client& user, Server& serv)
{
	(void) serv;
	if (user.getNickName().empty())
		return ;
		// return serv.putMsg(user, "tmp :plz use NICK <nick name>");
	if (user.getUserName().empty())
		return ;
		// return serv.putMsg(user, "tmp :plz use USER <user name>");

	if (user.getAuthenti() > 0)
		user.setAuthenti(2);
}

void Command::fPass(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	
	if (!serv.checkPass(cmd.arg(0)))
		return serv.putMsg(user, ERR_PASSWDMISMATCH(user.getNickName()));
	user.setAuthenti(1);
	checkAuthenti(user, serv);
}

bool checkName(std::string name)
{
	if (isdigit(name[0]))
		return true;
	if (name.find(',') != std::string::npos || \
		name.find(':') != std::string::npos || \
		name.find(' ') != std::string::npos || \
		name.find('*') != std::string::npos || \
		name.find('?') != std::string::npos || \
		name.find('!') != std::string::npos || \
		name.find('@') != std::string::npos )
		return true;
    for (size_t i = 0; i < name.size(); i++)
    {
        if (iscntrl(name[i]))
            return true;
    }
    return false;
}


void Command::fNick(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

	if (checkName(cmd.arg(0)))
		return serv.putMsg(user, ERR_ERRONEUSNICKNAME(user.getNickName(), cmd.arg(0)));
	
	if (serv.checkClient(cmd.arg(0)))
		return serv.putMsg(user, ERR_NICKNAMEINUSE(user.getNickName(), cmd.arg(0)));
	if (serv.checkClient(user.getNickName()))
		serv.rmClient(user);
	user.setNickName(cmd.arg(0));
	serv.addClient(cmd.arg(0), user);

	checkAuthenti(user, serv);
}


void Command::fUser(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	if (checkName(cmd.arg(0)))
		return serv.putMsg(user, ERR_ERRONEUSNICKNAME(user.getNickName(), cmd.arg(0)));
	user.setUserName(cmd.arg(0));
	checkAuthenti(user, serv);
}



/* ------------------------------------< commands >------------------------------------ */



void Command::fPing(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Command::fQuit(Client& user, Cmd& cmd)
{
	(void) cmd;
    (void) user;

	user.clearChannel();
    Server& serv = Server::getInstance();
	serv.rmClient(user);
}



void Command::fPrivmsg(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty() || cmd.arg(1).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

	std::vector<std::string> lstTarget(split(cmd.arg(0), ','));
	std::vector<std::string>::iterator itT(lstTarget.begin());

	if ((*itT)[0] == '#')
	{
		(*itT).erase(0,1);
		if (serv.findChannel((*itT)) == serv.endChannel())
			return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), (*itT)));

		Channel& channel = (*serv.findChannel((*itT))).second;
		if (channel.findUser(user.getFd()) <= 0)
			return serv.putMsg(user, ERR_USERNOTINCHANNEL(user.getNickName(),*itT));
		serv.putMsg(channel, user.getPrefix() + cmd.argcs(1));
	}
	else
	{
		if (serv.findClient((*itT)) == serv.endClientNick())
			return serv.putMsg(user, ERR_NOSUCHNICK(user.getNickName(),*itT));

		Client& client = (*serv.findClient((*itT))).second;
		serv.putMsg(client, cmd.argcs(1));
	}
}

void Command::fInvite(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty() || cmd.arg(1).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

	std::vector<std::string> lstUser(split(cmd.arg(0), ','));
	std::vector<std::string>::iterator itU(lstUser.begin()); 

    std::vector<std::string> lstChannel(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itC(lstChannel.begin());

	while (itU != lstUser.end())
	{
		if (serv.endClientNick() == serv.findClient(*itU))
			return serv.putMsg(user, ERR_NOSUCHNICK(user.getNickName(),*itU));
		Client invited(serv.findClient(*itU)->second);
		while (itC != lstChannel.end())
		{
			if ((*itC)[0] != '#')
				return serv.putMsg(user, ERR_BADCHANMASK(user.getNickName(), cmd.arg(0)));
			(*itC).erase(0,1);
			if (serv.findChannel((*itC)) == serv.endChannel())
				return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), (*itC)));

			Channel& channel = (*serv.findChannel((*itC))).second;
			if (channel.findUser(user.getFd()) <= 0)
				return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), channel.getName()));
			if (channel.findOperator(user.getFd()) <= 0)
				return serv.putMsg(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));

			channel.addInvite(invited.getFd());
			serv.putMsg(invited, user.getNickName() + " INVITE " + invited.getNickName() + ":#" + *itC);
			++itC;
		}
		++itU;
	}
}

bool isTokenMode(char c) {return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c == 'l');}

void Command::fMode(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	
	std::string name(cmd.arg(0));
	if (name[0] != '#')
		return serv.putMsg(user, ERR_BADCHANMASK(user.getNickName(), cmd.arg(0)));
	name.erase(0,1);
	if (serv.findChannel(name) == serv.endChannel())
		return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), name));

	Channel& channel = (*serv.findChannel(name)).second;

	if (channel.findUser(user.getFd()) <= 0)
		return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), channel.getName()));

	if (channel.findOperator(user.getFd()) <= 0)
		return serv.putMsg(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));

	size_t i(0);
	size_t mode(0);
	std::string str(cmd.arg(1));

	if (str[0] == '+')
		mode = 1;
	else if (str[0] != '-')
		return serv.putMsg(user, ERR_UMODEUNKNOWNFLAG(user.getNickName(), str[0]));

	for (std::string::iterator it = str.begin() + 1; it != str.end(); ++it)
	{
		if (!isTokenMode(*it))
			return serv.putMsg(user, ERR_UMODEUNKNOWNFLAG(user.getNickName(), *it));
		if (*it == 'l')
		{
			if (mode)
			{
				if (cmd.arg(2 + i).empty())
					return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
				channel.setMode(*it, atoi(cmd.arg(2 + i).c_str()));
				++i;
			}
			channel.setMode(*it, 0);
		}
		if (*it == 'k')
		{
			if (mode)
			{
				if (cmd.arg(2 + i).empty())
					return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
				channel.setPassword(cmd.arg(2 + i));
				++i;
			}
			else
				channel.setPassword(NULL);
		}
		if (*it == 'o')
		{
			if (cmd.arg(2 + i).empty())
				return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
			if (serv.findClient(cmd.arg(2 + i)) == serv.endClientNick())
				return serv.putMsg(user, ERR_USERNOTINCHANNEL(cmd.arg(2 + i),channel.getName()));
			Client client = (serv.findClient(cmd.arg(2 + i)))->second;
			if (channel.findUser(client.getFd()) <= 0)
				return serv.putMsg(user, ERR_USERNOTINCHANNEL(cmd.arg(2 + i),channel.getName()));
			channel.grade(mode, client.getFd());
			++i;
		}
		channel.setMode(*it, mode);
	}
	channel.log();
}

void Command::fTopic(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	
	std::string name(cmd.arg(0));
	if (name[0] != '#')
		return serv.putMsg(user, ERR_BADCHANMASK(user.getNickName(), cmd.arg(0)));
	name.erase(0,1);
	if (serv.findChannel(name) == serv.endChannel())
		return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), name));

	Channel& channel = (*serv.findChannel(name)).second;

	if (cmd.arg(1).empty())
	{
		if (channel.getTopic().empty())
			return serv.putMsg(user, channel.getName() + " :No topic is set");
		return serv.putMsg(user, channel.getName() + " :" + channel.getTopic());
	}
	if (channel.getMode('t') && channel.findOperator(user.getFd()) < 1)
		return serv.putMsg(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));
	channel.setTopic(cmd.argcs(1));
	logScript(LOG_TOPIC(toString(user.getFd()), user.getNickName(), channel.getName(), channel.getTopic()));
}

void Command::fKick(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

    std::vector<std::string> lstChannel(split(cmd.arg(0), ','));
    std::vector<std::string>::iterator itC(lstChannel.begin());

    std::vector<std::string> lstUser(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itU(lstUser.begin()); 

    std::string reason(cmd.arg(2)); // a verifier si argcs est le vrais comportement

    
    if (lstChannel.size() < 1 || lstUser.size() < 1 || reason.empty())
        return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
    
    while (itC != lstChannel.end())
    {
		if (itC->empty() || (*itC)[0] != '#' || !(*itC)[1])
            return serv.putMsg(user, ERR_BADCHANMASK(user.getNickName(), *itC));
        (*itC).erase(0,1);
		if (serv.findChannel(*itC) == serv.endChannel())
            return serv.putMsg(user, ERR_NOSUCHCHANNEL(user.getNickName(), *itC));
        Channel& channel = (*serv.findChannel(*itC)).second;
		channel.log();
        while (itU != lstUser.end())
        {
			if (serv.endClientNick() == serv.findClient(*itU))
            	return serv.putMsg(user, ERR_NOSUCHNICK(user.getNickName(),*itU));
       		Client& kicked = (*serv.findClient(*itU)).second;
			if (channel.findOperator(user.getFd()) <= 0)
				return serv.putMsg(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));
			if (channel.findUser(kicked.getFd()) <= 0)
				return serv.putMsg(user, ERR_USERNOTINCHANNEL(*itU,*itC));
			serv.putMsg(channel, user.getPrefix() + " KICK #" + channel.getName() + " " + reason );
			channel.rmUser(kicked.getFd());
			logScript(LOG_KCIK(toString(user.getFd()),user.getNickName(), kicked.getNickName(), channel.getName()));
            ++itU;
			(*serv.findChannel(*itC)).second.log(); // --------------------------------------------------- tmp
        }
        ++itC;
    }
}


void Command::fJoin(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();
    std::vector<std::string> joinChannel(split(cmd.arg(0), ','));
    
    if (joinChannel.size() < 1)
        return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

    std::vector<std::string> lstPassord(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itP(lstPassord.begin()); 
    for (std::vector<std::string>::iterator itC(joinChannel.begin()); itC != joinChannel.end(); ++itC)
    {
        if (!itC->empty() && (*itC)[0] == '#' && (*itC)[1])
        {
            (*itC).erase(0,1);
            if (serv.findChannel(*itC) != serv.endChannel())
            {
                Channel& channel = (*serv.findChannel(*itC)).second;
                if (channel.getMode('i') && channel.findInvite(user.getFd()) == -1)
                    return serv.putMsg(user, ERR_INVITEONLYCHAN(user.getNickName(), *itC));
                else if (channel.getMode('l'))
                    return serv.putMsg(user, ERR_CHANNELISFULL(user.getNickName(), *itC));        
                else if (channel.emptyPassword())
                    channel.addMember(user.getFd());
                else if (!lstPassord.empty() && channel.checkPassword(*itP++))
                    channel.addMember(user.getFd());
                else
                    return serv.putMsg(user, ERR_BADCHANNELKEY(user.getNickName(), *itC));
                logScript(LOG_JOIN_MEMBER(toString(user.getFd()), user.getNickName(), *itC));
				(*serv.findChannel(*itC)).second.log(); // --------------------------------------------------- tmp
            }
            else
            {
                if ((itP) != lstPassord.end())
                    serv.addChannel(*itC, Channel(*itC, user, *(itP++)));
                else
                    serv.addChannel(*itC, Channel(*itC, user));
				logScript(LOG_JOIN_OP(toString(user.getFd()), user.getNickName(), *itC));
                (*serv.findChannel(*itC)).second.addOperator(user.getFd());
				(*serv.findChannel(*itC)).second.log(); // --------------------------------------------------- tmp
            }
        }
        else
            return serv.putMsg(user, ERR_BADCHANMASK(user.getNickName(), *itC));
    }
}

Command::~Command() {}
Command::Command() {}

//vvv aga nick(), usr(), pwd() vvv

// void	Command::nickname(Client &user)
// {
// 	char	buffer[1000];//size?

// 	send(user.getFd(), "nickname: \n", 11, SOCK_NONBLOCK);
// 	recv(user.getFd(), buffer, sizeof(buffer), SOCK_NONBLOCK);//loop gnl?

// 	std::map<int, Client>::iterator it;
// 	it = ((Server::getInstance()).getMapClientsFd()).find(user.getFd());
// 	it->second.setNickname(buffer);
// 	if(user.getNickname() != "")
// 	{
// 		((Server::getInstance()).getMapClientsNick()).erase(user.getNickname());
// 	}
// 	((Server::getInstance()).getMapClientsNick()).insert({buffer, Client(user.getFd(), buffer, user.getUsername())});
// 	user.setNickname(buffer);
// }

// void	Command::username(Client &user)
// {
// 	char	buffer[1000];//size?

// 	send(user.getFd(), "username: \n", 11, SOCK_NONBLOCK);
// 	recv(user.getFd(), buffer, sizeof(buffer), SOCK_NONBLOCK);//loop gnl?

// 	std::map<int, Client>::iterator it;
// 	it = ((Server::getInstance()).getMapClientsFd()).find(user.getFd());
// 	it->second.setUsername(buffer);
// 	if (user.getNickname() != "")
// 	{
// 		std::map<std::string, Client>::iterator it2;
// 		it2 = ((Server::getInstance()).getMapClientsNick()).find(user.getNickname());
// 		it2->second.setUsername(buffer);
// 	}
// 	user.setUsername(buffer);
// }

// void	Command::password(Client &user)
// {
// 	char	*buffer[1000];//size?

// 	if (!user.getNickname() || !user.getUsername())
// 	{
// 		send(user.getFd(), "Please first enter a nickname and a username\n", 45, O_NONBLOCK);
// 		return ;
// 	}
// 	else if (user.getAuthen() == TRUE)
// 	{
// 		send(user.getFd(), "Already logged in.\n", 19, O_NONBLOCK);
// 		return ;
// 	}
// 	send(user.getFd(), "password: \n", 11, O_NONBLOCK);
// 	recv(user.getFd(), buffer, buffsize, O_NONBLOCK);//loop gnl?
// 	if(buffer == (Server::getInstance()).getPassword())//strcmp()? char*/string
// 		user.setAuthen(TRUE);
// }
