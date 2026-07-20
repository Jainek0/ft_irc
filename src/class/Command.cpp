#include "../_header/irc.hpp"

void checkAuthenti(Client& user, Server& serv)
{
	(void) serv;
	if (serv.getPassword().empty())
		user.setAuthenti(1);
	if (user.getNickName().empty())
		return ;
	if (user.getUserName().empty())
		return ;
	if (user.getAuthenti() > 0)
		user.setAuthenti(2);
}

mapCommand_t Command::createCommands()
{
    mapCommand_t commands;

    commands["KICK"] = &Command::fKick;
    commands["PART"] = &Command::fPart;
    commands["JOIN"] = &Command::fJoin;
    commands["MODE"] = &Command::fMode;
    commands["TOPIC"] = &Command::fTopic;
	commands["PRIVMSG"] = &Command::fPrivmsg;
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
		else if (cmd.command() == "QUIT")
			return fQuit(user, cmd);
		else if (cmd.command() != "CAP" && cmd.command() != "0")
			return serv.addBuffOut(user, ERR_NOTREGISTERED());
		checkAuthenti(user, serv);
	}
	else 
	{
		mapCommand_t::iterator itCmd(commands.find(cmd.command()));

		if (itCmd != commands.end())
			(itCmd->second)(user, cmd);
		else
			serv.addBuffOut(user, ERR_UNKNOWNCOMMAND(user.getNickName(), cmd.command()));
	}
}

/* ------------------------------------< commands >------------------------------------ */


void Command::fPass(Client& user, Cmd& cmd)
{
	Server& serv = Server::getInstance();

	if (serv.getPassword().empty())
		return ;
	if (cmd.arg(0).empty())
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	if (!serv.checkPass(cmd.arg(0)))
		return serv.addBuffOut(user, ERR_PASSWDMISMATCH(user.getNickName()));
	user.setAuthenti(1);
}

bool checkPrint(std::string name)
{
	for (std::string::iterator it(name.begin()); it != name.end(); ++it)
	{
		if (!std::isprint(*it))
			return true;
		if (std::iscntrl(*it))
			return true;
		if (std::isspace(*it))
			return true;
		if (*it == ':')
			return true;
	}
	return false;
}

bool checkName(std::string name)
{
	if (std::isdigit(name[0]))
		return true;
	if (checkPrint(name))
		return true;
	if (name.find(',') != std::string::npos || \
		name.find('*') != std::string::npos || \
		name.find('?') != std::string::npos || \
		name.find('!') != std::string::npos || \
		name.find('#') != std::string::npos || \
		name.find('@') != std::string::npos )
		return true;
    return false;
}


void Command::fNick(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	std::cout << cmd.arg(0) << std::endl;
	if (cmd.arg(0).empty())
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

	if (checkName(cmd.arg(0)) || !cmd.arg(1).empty())
		return serv.addBuffOut(user, ERR_ERRONEUSNICKNAME(user.getNickName(), cmd.arg(0)));
	
	if (user.getNickName() == cmd.arg(0))
		return ;
	
	if (!serv.checkClient(cmd.arg(0)))
	{
		return serv.addBuffOut(user, ERR_NICKNAMEINUSE(user.getNickName(), cmd.arg(0)));
	}
	for (std::set<std::string>::iterator it = user.getChannels().begin(); it != user.getChannels().end(); ++it)
	{
		serv.addBuffOut(serv.findChannel(*it)->second, RPL_NICK(user.getPrefix(), cmd.arg(0)));
	}
	serv.rmNick(user.getNickName());
	serv.addNick(cmd.arg(0), user.getFd());
	user.setNickName(cmd.arg(0));
}


void Command::fUser(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	if (checkName(cmd.arg(0)))
		return serv.addBuffOut(user, ERR_ERRONEUSUSERNAME(user.getNickName(), cmd.arg(0)));
	user.setUserName(cmd.arg(0));
}


/* ------------------------------------< commands >------------------------------------ */


void Command::fQuit(Client& user, Cmd& cmd)
{
	(void) cmd;

	user.clearChannel();
    Server& serv = Server::getInstance();
	serv.rmClient(user);
}

void Command::fPrivmsg(Client& user, Cmd& cmd)
{
	Server& serv = Server::getInstance();

	if (cmd.arg(0).empty() || cmd.arg(1).empty())
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

	std::vector<std::string> lstTarget(split(cmd.arg(0), ','));
	

	for (std::vector<std::string>::iterator itT(lstTarget.begin()); itT != lstTarget.end(); ++itT)
	{
		if ((*itT)[0] == '#')
		{
			(*itT).erase(0,1);
			if (serv.findChannel((*itT)) == serv.endChannel())
				return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), (*itT)));

			Channel& channel = (*serv.findChannel((*itT))).second;
			if (channel.findUser(user.getFd()) <= 0)
				return serv.addBuffOut(user, ERR_USERNOTINCHANNEL(user.getNickName(),*itT));
			serv.addBuffOut(channel, user, RPL_PRIVMSGCHANNEL(user.getPrefix(), channel.getName(), cmd.argcs(1)));
		}
		else
		{
			if (serv.findClient((*itT)) == serv.endClientFd())
				return serv.addBuffOut(user, ERR_NOSUCHNICK(user.getNickName(),*itT));

			Client& target = (*serv.findClient((*itT))).second;
			serv.addBuffOut(target, RPL_PRIVMSGUSER(user.getPrefix(), target.getNickName(), cmd.argcs(1)));
		}
	}
}

void Command::fInvite(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty() || cmd.arg(1).empty())
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

	std::vector<std::string> lstUser(split(cmd.arg(0), ','));
	std::vector<std::string>::iterator itU(lstUser.begin());

    std::vector<std::string> lstChannel(split(cmd.arg(1), ','));

	while (itU != lstUser.end())
	{
		if (serv.endClientFd() == serv.findClient(*itU))
			return serv.addBuffOut(user, ERR_NOSUCHNICK(user.getNickName(),*itU));
		Client invited(serv.findClient(*itU)->second);

    	std::vector<std::string>::iterator itC = lstChannel.begin();
		while (itC != lstChannel.end())
		{
			if ((*itC)[0] != '#' || checkPrint(*itC))
				return serv.addBuffOut(user, ERR_BADCHANMASK(user.getNickName(), *itC));
			(*itC).erase(0,1);
			if (serv.findChannel((*itC)) == serv.endChannel())
				return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), (*itC)));

			Channel& channel = (*serv.findChannel((*itC))).second;
			if (channel.findUser(user.getFd()) <= 0)
				return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), channel.getName()));
			if (channel.getMode('i') && channel.findOperator(user.getFd()) <= 0)
				return serv.addBuffOut(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));

			channel.addInvite(invited.getFd());
			std::cout << "log invite : " << RPL_INVITERCVR(user.getPrefix(), invited.getNickName(), *itC) << std::endl;
			serv.addBuffOut(invited, RPL_INVITERCVR(user.getPrefix(), invited.getNickName(), *itC));
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
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	
	std::string name(cmd.arg(0));
	if (name[0] != '#')
		return serv.addBuffOut(user, ERR_BADCHANMASK(user.getNickName(), cmd.arg(0)));
	name.erase(0,1);
	if (serv.findChannel(name) == serv.endChannel())
		return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), name));

	Channel& channel = (*serv.findChannel(name)).second;

	if (channel.findUser(user.getFd()) <= 0)
		return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), channel.getName()));

	if (channel.findOperator(user.getFd()) <= 0)
		return serv.addBuffOut(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));

	if (cmd.arg(1).empty())
	{
		return serv.addBuffOut(user, RPL_PRINT_MODE(user.getNickName(), channel.getName(), channel.getMode()));
	}

	size_t i(0);
	size_t mode(0);
	std::string str(cmd.arg(1));

	if (str[0] == '+')
		mode = 1;
	else if (str[0] != '-')
		return serv.addBuffOut(user, ERR_UMODEUNKNOWNFLAG(user.getNickName(), str[0]));

	for (std::string::iterator it = str.begin() + 1; it != str.end(); ++it)
	{
		if (!isTokenMode(*it))
			return serv.addBuffOut(user, ERR_UMODEUNKNOWNFLAG(user.getNickName(), *it));
		if (*it == 'l')
		{
			if (mode)
			{
				if (cmd.arg(2 + i).empty())
					return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
				channel.setMode(*it, toSize_t(cmd.arg(2 + i)));
				serv.addBuffOut(user, RPL_MODE_P(user.getPrefix(), channel.getName(), *it, cmd.arg(2 + i)));
				++i;
			}
			else
			{
				channel.setMode(*it, 0);
				serv.addBuffOut(user, RPL_MODE_M(user.getPrefix(), channel.getName(), *it, ""));
			}
			continue;
		}
		else if (*it == 'k')
		{
			if (mode)
			{
				if (cmd.arg(2 + i).empty())
					return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
				channel.setPassword(cmd.arg(2 + i));
				serv.addBuffOut(user, RPL_MODE_P(user.getPrefix(), channel.getName(), *it, ""));
				++i;
			}
			else
			{
				channel.setPassword("");
				serv.addBuffOut(user, RPL_MODE_M(user.getPrefix(), channel.getName(), *it, ""));
			}
			continue;
		}
		else if (*it == 'o')
		{
			if (cmd.arg(2 + i).empty())
				return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
			if (serv.findClient(cmd.arg(2 + i)) == serv.endClientFd())
				return serv.addBuffOut(user, ERR_USERNOTINCHANNEL(cmd.arg(2 + i),channel.getName()));
			Client client = (serv.findClient(cmd.arg(2 + i)))->second;
			if (channel.findUser(client.getFd()) <= 0)
				return serv.addBuffOut(user, ERR_USERNOTINCHANNEL(cmd.arg(2 + i),channel.getName()));
			channel.grade(mode, client.getFd());
			if (mode)
				serv.addBuffOut(channel, RPL_MODE_P(user.getPrefix(), channel.getName(), *it, cmd.arg(2 + i)));
			else
				serv.addBuffOut(channel, RPL_MODE_M(user.getPrefix(), channel.getName(), *it, cmd.arg(2 + i)));    
			channel.checkOperator();
			++i;
			continue;
		}
		channel.setMode(*it, mode);
		if (mode)
			serv.addBuffOut(user, RPL_MODE_P(user.getPrefix(), channel.getName(), *it, ""));
		else
			serv.addBuffOut(user, RPL_MODE_M(user.getPrefix(), channel.getName(), *it, ""));
	}
	channel.log();
}

void Command::fTopic(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

	if (cmd.arg(0).empty())
		return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
	
	std::string name(cmd.arg(0));
	if (name[0] != '#')
		return serv.addBuffOut(user, ERR_BADCHANMASK(user.getNickName(), cmd.arg(0)));
	name.erase(0,1);
	if (serv.findChannel(name) == serv.endChannel())
		return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), name));

	Channel& channel = (*serv.findChannel(name)).second;

	if (cmd.arg(1).empty())
	{
		if (channel.getTopic().empty())
			return serv.addBuffOut(channel, RPL_NOTOPIC(user.getNickName(), channel.getName()));
		return serv.addBuffOut(user, RPL_TOPIC(user.getPrefix(), channel.getName(), channel.getTopic()));
	}
	if (channel.getMode('t') && channel.findOperator(user.getFd()) < 1)
		return serv.addBuffOut(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));
	channel.setTopic(cmd.argcs(1));
	serv.addBuffOut(channel, RPL_TOPIC(user.getPrefix(), channel.getName(), cmd.argcs(1)));
	logScript(LOG_TOPIC(toString(user.getFd()), user.getNickName(), channel.getName(), channel.getTopic()));
}

void Command::fPart(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

    std::vector<std::string> lstChannel(split(cmd.arg(0), ','));
    std::vector<std::string>::iterator itC(lstChannel.begin());

   
    if (lstChannel.size() < 1)
        return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
    
    while (itC != lstChannel.end())
    {
		if (itC->empty() || (*itC)[0] != '#' || !(*itC)[1])
            return serv.addBuffOut(user, ERR_BADCHANMASK(user.getNickName(), *itC));
        (*itC).erase(0,1);
		if (serv.findChannel(*itC) == serv.endChannel())
            return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), *itC));
        Channel& channel = (*serv.findChannel(*itC)).second;
		if (channel.findUser(user.getFd()) <= 0)
			return serv.addBuffOut(user, ERR_USERNOTINCHANNEL(user.getNickName(),*itC));
		serv.addBuffOut(channel, RPL_PART(user.getPrefix(), channel.getName()));
		channel.rmUser(user.getFd());
		logScript(LOG_PART(toString(user.getFd()),user.getNickName(), channel.getName()));
		channel.log();
        ++itC;
		if (channel.checkOperator())
			serv.rmChannel(channel.getName());
    }
}


void Command::fKick(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();

    std::vector<std::string> lstChannel(split(cmd.arg(0), ','));
    std::vector<std::string>::iterator itC(lstChannel.begin());

    std::vector<std::string> lstUser(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itU(lstUser.begin()); 

    std::string reason(cmd.arg(2));

    
    if (lstChannel.size() < 1 || lstUser.size() < 1 || reason.empty())
        return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
    
    while (itC != lstChannel.end())
    {
		if (itC->empty() || (*itC)[0] != '#' || !(*itC)[1])
            return serv.addBuffOut(user, ERR_BADCHANMASK(user.getNickName(), *itC));
        (*itC).erase(0,1);
		if (serv.findChannel(*itC) == serv.endChannel())
            return serv.addBuffOut(user, ERR_NOSUCHCHANNEL(user.getNickName(), *itC));
        Channel& channel = (*serv.findChannel(*itC)).second;
        while (itU != lstUser.end())
        {
			if (serv.endClientFd() == serv.findClient(*itU))
            	return serv.addBuffOut(user, ERR_NOSUCHNICK(user.getNickName(),*itU));
       		Client& kicked = (*serv.findClient(*itU)).second;
			if (channel.findOperator(user.getFd()) <= 0)
				return serv.addBuffOut(user, ERR_CHANOPRIVSNEEDED(user.getNickName(), channel.getName()));
			if (channel.findUser(kicked.getFd()) <= 0)
				return serv.addBuffOut(user, ERR_USERNOTINCHANNEL(*itU,*itC));
			serv.addBuffOut(channel, RPL_KICK(user.getPrefix(), channel.getName(), kicked.getNickName(), reason));
			channel.rmUser(kicked.getFd());
			logScript(LOG_KCIK(toString(user.getFd()),user.getNickName(), kicked.getNickName(), channel.getName()));
            ++itU;
        }
		(*serv.findChannel(*itC)).second.log();
		++itC;
		if (channel.checkOperator())
			serv.rmChannel(channel.getName());
    }
}


void rpl_lst(Client& user, Channel& channel)
{
    Server& serv = Server::getInstance();


	std::string lst;
	serv.addBuffOut(channel, RPL_JOIN(user.getPrefix(), channel.getName()));
	for (std::set<int>::iterator it = channel.getOperator().begin(); it != channel.getOperator().end(); ++it)
	{
		lst +=  "@" + serv.findClient(*it)->second.getNickName() + " ";
	}
	for (std::set<int>::iterator it = channel.getMember().begin(); it != channel.getMember().end(); ++it)
	{
		lst +=  serv.findClient(*it)->second.getNickName() + " ";
	}
	serv.addBuffOut(user, RPL_NAMEREPLY(user.getNickName(), channel.getName(), lst));
	serv.addBuffOut(user, RPL_ENDLISTCLIENT(user.getNickName(), channel.getName()));
}

void Command::fJoin(Client& user, Cmd& cmd)
{
    Server& serv = Server::getInstance();
    std::vector<std::string> joinChannel(split(cmd.arg(0), ','));
    
    if (joinChannel.size() < 1)
        return serv.addBuffOut(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));

    std::vector<std::string> lstPassord(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itP(lstPassord.begin()); 
    for (std::vector<std::string>::iterator itC(joinChannel.begin()); itC != joinChannel.end(); ++itC)
    {
        if (!itC->empty() && (*itC)[0] == '#' && (*itC)[1] && !checkPrint(*itC))
        {
            (*itC).erase(0,1);
            if (serv.findChannel(*itC) != serv.endChannel())
            {
                Channel& channel = (*serv.findChannel(*itC)).second;
				if (channel.findUser(user.getFd()) != -1)
					return ;
                if (channel.getMode('i') && channel.findInvite(user.getFd()) == -1)
                    return serv.addBuffOut(user, ERR_INVITEONLYCHAN(user.getNickName(), *itC));
                else if (channel.getMode('l'))
                    return serv.addBuffOut(user, ERR_CHANNELISFULL(user.getNickName(), *itC));        
                else if (channel.emptyPassword())
				{
					channel.addMember(user.getFd());
					rpl_lst(user, channel);
				}
                else if (!lstPassord.empty() && channel.checkPassword(*itP++))
				{
					channel.addMember(user.getFd());
					rpl_lst(user, channel);
				}
                else
                    return serv.addBuffOut(user, ERR_BADCHANNELKEY(user.getNickName(), *itC));
                logScript(LOG_JOIN_MEMBER(toString(user.getFd()), user.getNickName(), *itC));
				(*serv.findChannel(*itC)).second.log();
            }
            else
            {
                if ((itP) != lstPassord.end())
                    serv.addChannel(*itC, Channel(*itC, user, *(itP++)));
                else
                    serv.addChannel(*itC, Channel(*itC, user));
				(*serv.findChannel(*itC)).second.addOperator(user.getFd());
				(*serv.findChannel(*itC)).second.log();
				rpl_lst(user, (*serv.findChannel(*itC)).second);
				logScript(LOG_JOIN_OP(toString(user.getFd()), user.getNickName(), *itC));
            }
        }
        else
            return serv.addBuffOut(user, ERR_BADCHANMASK_O(user.getNickName(), *itC));
    }
}

Command::~Command() {}
Command::Command() {}