

#include "../header/irc.hpp"

Server::Server(int pid, std::string password)
    : _pid(pid), _pasword(password) 
{
    _commands = createCommands();
}

Server::Server(const Server &other)
    : _pid(other._pid), _pasword(other._pasword), _clients(other._clients), _channels(other._channels), _commands(other._commands)
{}

// Server& Server::operator=(const Server &other)
// {
//     if (this != &other)
//     {
//         _clients = other._clients;
//         _channels = other._channels;
//     }
//     return *this;
// }

Server::~Server() {}


void Server::removeClient(int pid)
{
    _clients.erase(pid);
}


Client&	Server::findClient(int pid)
{
    return (_clients.find(pid))->second;
}

bool Server::checkClient(int pid) const
{
    return (_clients.find(pid) != _clients.end());
}



/* ------------------------------------< work in progres >------------------------------------ */

void Server::acceptClient(int pid)
{
    // demander le password du serv ici, avent de creer user, puis completer info client.
    Client tmp(pid, "kilian", "le bg");
    _clients.insert(std::make_pair(pid, tmp));

    
}

void Server::handleCommand(Client& user, std::string str)
{
    Cmd cmd(str);
    std::map<std::string, void (Server::*)(Client&, Cmd&)>::iterator itCmd(_commands.find(cmd.command()));

    if (itCmd != _commands.end())
        (this->*itCmd->second)(user, cmd);
    else
        std::cout << "unknown command : " << cmd.command() << std::endl; // a revioller au client
}