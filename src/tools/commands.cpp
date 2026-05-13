
#include "../header/irc.hpp"

std::map<std::string, void (Server::*)(Client&, Cmd&)> Server::createCommands()
{
    std::map<std::string, void (Server::*)(Client&, Cmd&)> commands;

    commands["KICK"] = &Server::kick;
    commands["JOIN"] = &Server::join;
    commands["MODE"] = &Server::mode;
    commands["TOPIC"] = &Server::topic;


    return commands;
}

/* ------------------------------------< commands >------------------------------------ */

void Server::kick(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Server::mode(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}

void Server::topic(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
}


void Server::join(Client& user, Cmd& cmd)
{
    std::vector<std::string> joinChannel(split(cmd.arg(0), ','));
    if (joinChannel.size() < 1)
    {
        putMsg(user, ERR_NEEDMOREPARAMS(user.nick(), cmd.command()));
        return ;
    }
    std::vector<std::string> lstPassord(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itP(lstPassord.begin()); 
    for (std::vector<std::string>::iterator itC(joinChannel.begin()); itC != joinChannel.end(); ++itC)
    {
        if (!itC->empty() && (*itC)[0] == '#')
        {
            (*itC).erase(0,1);
            if (itC->empty())
                continue;
            if (_channels.find(*itC) != _channels.end())
            {
                Channel tmp((*_channels.find(*itC)).second);
                if (tmp.getMode('i'))
                    return putMsg(user, ERR_INVITEONLYCHAN(user.nick(), *itC));
                else if (tmp.getMode('l'))
                    return putMsg(user, ERR_CHANNELISFULL(user.nick(), *itC));        
                else if (tmp.emptyPassword())
                    tmp.addOperator(user.fd());
                else if (tmp.getPassword() == *itP)
                    tmp.addMember(user.fd());
                else
                    return putMsg(user, ERR_BADCHANNELKEY(user.nick(), *itC));
                logScript(LOG_JOIN(user.nick(), *itC));
            }
            else
            {
                if ((itP) != lstPassord.end())
                {
                    Channel tmp(*itC, user, *(itP));
                    _channels.insert(make_pair(tmp.channelName(), tmp));
                    ++itP;
                }
                else
                {
                    Channel tmp(*itC, user);
                    _channels.insert(make_pair(tmp.channelName(), tmp));
                }
            }
        }
        else
            return putMsg(user, ERR_BADCHANMASK(user.nick(), *itC));
    }
}

