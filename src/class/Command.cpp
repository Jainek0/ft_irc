
#include "../_header/irc.hpp"


mapCommand_t Command::createCommands()
{
    mapCommand_t commands;

    commands["KICK"] = &Command::kick;
    commands["JOIN"] = &Command::join;
    commands["MODE"] = &Command::mode;
    commands["TOPIC"] = &Command::topic;

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

void Command::kick(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
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

void Command::mode(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Command::topic(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
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
                else if (!lstPassord.empty() && channel.checkPassword(*itP))
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