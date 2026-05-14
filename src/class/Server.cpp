

#include "../_header/irc.hpp"

Server::Server(int fd, std::string password)
	: _fd(fd), _password(password) 
{
	logScript( LOG_START(toString(fd)));
}

Server::Server(const Server &other)
	: _fd(other._fd), _password(other._password), _clientsFd(other._clientsFd), _clientsNick(other._clientsNick), _channels(other._channels)
{}

Server& Server::getInstance(int fd, std::string password) 
{
	static Server server(fd, password);
	return server;
}

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

void Server::rmClient(int fd)
{
	_clientsNick.erase(_clientsFd.find(fd)->second.getNick());
	_clientsFd.erase(fd);
}

void Server::rmClient(const std::string nick)
{
	_clientsFd.erase(_clientsNick.find(nick)->second.fd());
	_clientsNick.erase(nick);
}

void Server::addClient(const int fd, Client user)
{
	_clientsFd.insert(std::make_pair(fd, user));
	_clientsNick.insert(std::make_pair(user.getNick(), user));
}

void Server::addClient(const std::string nick, Client user)
{ 
	_clientsFd.insert(std::make_pair(user.fd(), user));
	_clientsNick.insert(std::make_pair(nick, user));
}

void Server::addChannel(const std::string name, Channel channel)
{ 
	_channels.insert(std::make_pair(name, channel));
}



mapClient_i_t::iterator    	Server::findClient(const int fd)					{ return (_clientsFd.find(fd)); }

mapClient_s_t::iterator    	Server::findClient(const std::string nick)			{ return (_clientsNick.find(nick)); }

mapChannel_t::iterator     	Server::findChannel(const std::string name)			{ return (_channels.find(name)); }


mapClient_i_t::iterator    	Server::endClientFd()                   			{ return (_clientsFd.end()); }

mapClient_s_t::iterator    	Server::endClientNick()         					{ return (_clientsNick.end()); }

mapChannel_t::iterator     	Server::endChannel()        						{ return (_channels.end()); }


mapClient_i_t::iterator    	Server::beginClientFd()                 			{ return (_clientsFd.begin()); }

mapClient_s_t::iterator    	Server::beginClientNick()       					{ return (_clientsNick.begin()); }

mapChannel_t::iterator     	Server::beginChannel()      						{ return (_channels.begin()); }


bool                       	Server::checkClient(const int fd) const            	{ return (_clientsFd.find(fd) != _clientsFd.end()); }

bool                       	Server::checkClient(const std::string nick) const  	{ return (_clientsNick.find(nick) != _clientsNick.end()); }


/* ------------------------------------< work in progres >------------------------------------ */

void Server::acceptClient()
{
	// demander le password du serv ici, avent de creer user, puis completer info client.
	Client tmp(4242);


	tmp.setNick("Kilian");
	tmp.setNick("le bg");
	_clientsFd.insert(std::make_pair(4242, tmp));
	_clientsNick.insert(std::make_pair(tmp.getNick(), tmp));
	logScript(LOG_ACCEPTCLIENT(toString(3232), toString(4242)));
}

/*      a changer pour envoiler les msg a target et pas le print comme actuellement     */
void	Server::putMsg(Client target, std::string msg)	const
{
	std::cout << "[" << target.getNick() + "] " \
	+ msg << std::endl;
}