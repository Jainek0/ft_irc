

#include "../header/irc.hpp"


Server::Server()
{}

Server::Server(int pid, std::string password)
    : _pid(pid), _pasword(password) 
{
    _commands = createCommands();
}

Server::Server(const Server &other)
    : _pid(other._pid), _pasword(other._pasword), _clients(other._clients), _channels(other._channels), _commands(other._commands)
{}

Server& Server::operator=(const Server &other)
{
    if (this != &other) {
        _pid = other._pid;
        _pasword = other._pasword;
        _clients = other._clients;
        _channels = other._channels;
    }
    return *this;
}

Server::~Server() {}

void Server::handleCommand(int pid, std::string str)
{
    Cmd cmd(str);
    std::map<std::string, void (Server::*)(Client&, Cmd&)>::iterator it = _commands.find(cmd._command);

    if (it != _commands.end())
        (this->*it->second)(_clients[pid], cmd);
    else
        std::cout << "unknown command : " << cmd._command << std::endl;
}


/* ------------------------------------< work in progres >------------------------------------ */

void Server::acceptClient(int pid)
{
    // demander le password du serv ici, avent de creer user, puis completer info client.
    Client tmp(pid, "kilian", "le bg");
    _clients[pid] = tmp;
}

// void Server::removeClient(std::string nickUser) {}

