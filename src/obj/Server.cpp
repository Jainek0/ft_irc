

#include "../header/irc.hpp"

Server::Server(int fd, std::string password)
    : _fd(fd), _pasword(password) 
{
    _commands = createCommands();
    logScript( LOG_START(toString(fd)));
}

Server::Server(const Server &other)
    : _fd(other._fd), _pasword(other._pasword), _clientsFd(other._clientsFd), _clientsNick(other._clientsNick), _channels(other._channels), _commands(other._commands)
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

Server::~Server()
{
    logScript(LOG_END(toString(_fd)));
}

void Server::removeClient(int fd)
{
    _clientsNick.erase(_clientsFd.find(fd)->second.nick());
    _clientsFd.erase(fd);
}

void Server::removeClient(const std::string nick)
{
    _clientsFd.erase(_clientsNick.find(nick)->second.fd());
    _clientsNick.erase(nick);
}


Client&	Server::findClient(const int fd)                { return (_clientsFd.find(fd))->second; }

Client&	Server::findClient(const std::string nick)      { return (_clientsNick.find(nick))->second; }

bool Server::checkClient(const int fd) const            { return (_clientsFd.find(fd) != _clientsFd.end()); }

bool Server::checkClient(const std::string nick) const  { return (_clientsNick.find(nick) != _clientsNick.end()); }


/* ------------------------------------< work in progres >------------------------------------ */

void Server::acceptClient(int fd)
{
    // demander le password du serv ici, avent de creer user, puis completer info client.
    Client tmp(fd, "kilian", "le bg");
    _clientsFd.insert(std::make_pair(fd, tmp));
    _clientsNick.insert(std::make_pair(tmp.nick(), tmp));
    logScript(LOG_ACCEPTCLIENT(toString(fd), tmp.nick(), tmp.getUsername()));
}

void Server::handleCommand(Client& user, std::string str)
{
    Cmd cmd(str);
    std::map<std::string, void (Server::*)(Client&, Cmd&)>::iterator itCmd(_commands.find(cmd.command()));

    if (itCmd != _commands.end())
        (this->*itCmd->second)(user, cmd);
    else
        std::cout << "unknown command : " << cmd.command() << std::endl; // a renvoiler au client,  l err n est pas la 
}

void	Server::putMsg(Client target, std::string msg)	const
{
    std::cout << "[" << target.nick() + "] " + msg << std::endl; // a renvoiler a target
}