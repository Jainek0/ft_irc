
#include "../_header/irc.hpp"


mapCommand_t Command::createCommands()
{
    mapCommand_t commands;

    commands["KICK"] = &Command::kick;
    commands["JOIN"] = &Command::join;
    commands["MODE"] = &Command::mode;
    commands["TOPIC"] = &Command::topic;
	commands["PRIVMSG"] = &Command::privmsg;
    commands["PING"] = &Command::ping;
    commands["QUIT"] = &Command::quit;
    commands["INVITE"] = &Command::invite;

    return commands;
}

void Command::handleCommand(Client& user, std::string str)
{
    static mapCommand_t commands = createCommands();
    Server& serv = Server::getInstance();
    
    Cmd cmd(str);
    mapCommand_t::iterator itCmd(commands.find(cmd.command()));

    if (itCmd != commands.end())
        (itCmd->second)(user, cmd);
    else
        serv.putMsg(user, ERR_UNKNOWNCOMMAND(user.getNickName(), cmd.command()));
}

/* ------------------------------------< commands >------------------------------------ */

void Command::privmsg(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Command::ping(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Command::quit(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Command::invite(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}



	// 	· i: Set/remove Invite-only channel
	// 	· t: Set/remove the restrictions of the TOPIC command to channel
	// 	operators
	// 	· k: Set/remove the channel key (password)
	// 	· o: Give/take channel operator privilege
	// 	· l: Set/remove the user limit to channel

bool isTokenMode(char c) {return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c == 'l');}

void Command::mode(Client& user, Cmd& cmd)
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
			if (cmd.arg(2 + i).empty())
				return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNickName(), cmd.command()));
			channel.setPassword(cmd.arg(2 + i));
			++i;
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

void Command::topic(Client& user, Cmd& cmd)
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



void Command::kick(Client& user, Cmd& cmd)
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


void Command::join(Client& user, Cmd& cmd)
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
                if (channel.getMode('i'))
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