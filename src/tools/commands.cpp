
#include "../header/irc.hpp"

std::map<std::string, void (Server::*)(Client&, Cmd&)> Server::createCommands()
{
    std::map<std::string, void (Server::*)(Client&, Cmd&)> commands;

    commands["KICK"] = &Server::kick;
    commands["JOIN"] = &Server::join;

    return commands;
}

/* ------------------------------------< commands >------------------------------------ */

void Server::kick(Client& user, Cmd& cmd)
{
    (void) user;
    (void) cmd;
    std::cout << "KICK\n";
}

void Server::join(Client& user, Cmd& cmd)
{
    std::vector<std::string> joiChannel(split(cmd.arg(0), ','));
    std::vector<std::string> lstPassord(split(cmd.arg(1), ','));
    std::vector<std::string>::iterator itP(lstPassord.begin()); 
    for (std::vector<std::string>::iterator itC(joiChannel.begin()); itC != joiChannel.end(); ++itC)
    {
        if (!itC->empty() && (*itC)[0] == '#')
        {
            (*itC).erase(0,1);
            if (itC->empty())
                continue;
            if (_channels.find(*itC) != _channels.end())
            {
                Channel tmp((*_channels.find(*itC)).second);
                if (tmp.emptyPassword())
                    tmp.addOperator(user.fd());
                else if (tmp.getPassword() == *itP)
                    tmp.addMember(user.fd());
                else
                {
                    std::cerr << "bad password for join <" << *itC << ">" << std::endl; // a renvoiler au client
                    break;
                }
                logScript("<" + user.nick() + "> join <" + *itC + ">\n");
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
        {
            std::cerr << "unknown :" << *itC << std::endl; // a renvoiler au client
            break;
        }
    }
}
