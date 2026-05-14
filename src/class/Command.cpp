
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
        serv.putMsg(user, ERR_UNKNOWNCOMMAND(cmd.command()));
}

/* ------------------------------------< commands >------------------------------------ */

void Command::kick(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
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
        return serv.putMsg(user, ERR_NEEDMOREPARAMS(user.getNick(), cmd.command()));

    std::vector<std::string> lstPassord(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itP(lstPassord.begin()); 
    for (std::vector<std::string>::iterator itC(joinChannel.begin()); itC != joinChannel.end(); ++itC)
    {
        if (!itC->empty() && (*itC)[0] == '#' && (*itC)[1])
        {
            (*itC).erase(0,1);
            if (serv.findChannel(*itC) != serv.endChannel())
            {
                Channel tmp((*serv.findChannel(*itC)).second);
                if (tmp.getMode('i'))
                    return serv.putMsg(user, ERR_INVITEONLYCHAN(user.getNick(), *itC));
                else if (tmp.getMode('l'))
                    return serv.putMsg(user, ERR_CHANNELISFULL(user.getNick(), *itC));        
                else if (tmp.emptyPassword())
                    tmp.addOperator(user.fd());
                else if (!lstPassord.empty() && tmp.checkPassword(*itP))
                    tmp.addMember(user.fd());
                else
                    return serv.putMsg(user, ERR_BADCHANNELKEY(user.getNick(), *itC));
                logScript(LOG_JOIN(toString(user.fd()), user.getNick(), *itC));
            }
            else
            {
                if ((itP) != lstPassord.end())
                    serv.addChannel(*itC, Channel(*itC, user, *(itP++)));
                else
                    serv.addChannel(*itC, Channel(*itC, user));
            }
        }
        else
            return serv.putMsg(user, ERR_BADCHANMASK(user.getNick(), *itC));
    }
}

Command::~Command() {}
Command::Command() {}