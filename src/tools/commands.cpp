
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
    std::vector<std::string> joiChannel;
    std::vector<std::string> lstPassord;
    if (cmd._args.size() > 0 && !cmd._args[0].empty())
        joiChannel = split(cmd._args[0], ',');
    if (cmd._args.size() > 1 && !cmd._args[1].empty())
        lstPassord = split(cmd._args[1], ',');
    std::vector<std::string>::iterator itP = lstPassord.begin(); 
    for (std::vector<std::string>::iterator itC = joiChannel.begin(); itC != joiChannel.end(); ++itC)
    {
        if (!itC->empty() && (*itC)[0] == '#')
        {
            (*itC).erase(0,1);
            if (itC->empty())
                continue;
            if (_channels.find(*itC) != _channels.end())
            {
                Channel tmp((*_channels.find(*itC)).second);
                if (tmp._pasword.empty())
                    tmp._members.insert(user._nick);
                else if (tmp._pasword == *itP)
                    tmp._members.insert(user._nick);
                else
                {
                    std::cerr << "bad password for join <" << *itC << ">" << std::endl; // a renvoiler au client
                    break;
                }
                std::cout << "<" << user._nick << "> join <" << *itC << ">" << std::endl;
            }
            else
            {
                if ((itP) != lstPassord.end())
                {
                    Channel tmp(*itC, user._nick, *(itP));
                    _channels[tmp._channel_name] = tmp;
                    ++itP;
                }
                else
                {
                    Channel tmp(*itC, user._nick);
                    _channels[tmp._channel_name] = tmp;
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
