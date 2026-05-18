

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
	_clientsNick.erase(_clientsFd.find(fd)->second.getNickName());
	_clientsFd.erase(fd);
}

void Server::rmClient(const std::string Name)
{
	_clientsFd.erase(_clientsNick.find(Name)->second.getFd());
	_clientsNick.erase(Name);
}

void Server::addClient(const int fd, Client user)
{
	_clientsFd.insert(std::make_pair(fd, user));
	_clientsNick.insert(std::make_pair(user.getNickName(), user));
}

void Server::addClient(const std::string Name, Client user)
{ 
	_clientsFd.insert(std::make_pair(user.getFd(), user));
	_clientsNick.insert(std::make_pair(Name, user));
}

void Server::addChannel(const std::string name, Channel channel)
{ 
	_channels.insert(std::make_pair(name, channel));
}



mapClient_i_t::iterator    		Server::findClient(const int fd)					{ return (_clientsFd.find(fd)); }

mapClient_s_t::iterator    		Server::findClient(const std::string Name)			{ return (_clientsNick.find(Name)); }

mapChannel_t::iterator    		Server::findChannel(const std::string name)			{ return (_channels.find(name)); }


mapClient_i_t::const_iterator 	Server::endClientFd()     					const	{ return (_clientsFd.end()); }

mapClient_s_t::const_iterator 	Server::endClientNick()   					const	{ return (_clientsNick.end()); }

mapChannel_t::const_iterator  	Server::endChannel()      					const	{ return (_channels.end()); }


mapClient_i_t::iterator    		Server::beginClientFd()                 			{ return (_clientsFd.begin()); }

mapClient_s_t::iterator    		Server::beginNick()       							{ return (_clientsNick.begin()); }

mapChannel_t::iterator     		Server::beginChannel()      						{ return (_channels.begin()); }


bool                       		Server::checkClient(const int fd) 			const	{ return (_clientsFd.find(fd) != _clientsFd.end()); }

bool                       		Server::checkClient(const std::string nick)	const  	{ return (_clientsNick.find(nick) != _clientsNick.end()); }

bool                       		Server::checkPass(const std::string pass)	const  	{ return (_password == pass); }





/* ------------------------------------< work in progres >------------------------------------ */

void Server::acceptClient()
{
	Client tmp(4242);


	tmp.setNickName("le_bg");
	tmp.setUserName("kilian");
	tmp.setAuthenti();

	_clientsFd.insert(std::make_pair(4242, tmp));
	_clientsNick.insert(std::make_pair(tmp.getNickName(), tmp));
	logScript(LOG_ACCEPTCLIENT(toString(3232), toString(4242)));
}

/*      a changer pour envoiler les msg a target et pas le print comme actuellement     */
void	Server::putMsg(const Client& target, const std::string& msg)	const
{
	std::cout << "[" << target.getNickName() + "] " + msg << std::endl;
}

void	Server::putMsg(const Channel& target, const std::string& msg) const
{
	target.log();
	std::set<int> lst(target.getUser());
	for (std::set<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << "[" << toString(*it) + "] " + msg << std::endl;
}