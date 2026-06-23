#include "../_header/irc.hpp"


//constructor/destructor
Server::Server(int port, std::string password)
	: _port(port), _password(password) 
{
	logScript( LOG_START(toString(port)));
}

Server::Server(const Server &other)
	: _port(other._port), _servFd(other._servFd), _password(other._password), _clientsFd(other._clientsFd), _clientsNick(other._clientsNick), _channels(other._channels)
{}

Server& Server::getInstance(int port, std::string password) 
{
	static Server server(port, password);
	return server;
}

void	Server::setup(void)
{
	_servFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_servFd == -1)
	{
		std::cerr << "socket()";
		throw Server::SetupErrorException();
	}
	//if (setsockopt(SO_REUSEADDR));??
	//int endian = 1;
	//setsockopt(_servfd, SOL_SOCKET, SO_REUSEADDR, &endian, sizeof(endian));
	if (fcntl(_servFd, F_SETFL ,O_NONBLOCK))
	{
		std::cerr << "fcntl()";
		throw Server::SetupErrorException();
	}

	//vv set values in the sockaddr struct vv
	_servaddr.sin_family = AF_INET;
	_servaddr.sin_port = htons(_port);
	inet_pton(AF_INET, "127.0.0.1", &(_servaddr.sin_addr));

	if (bind(_servFd, (struct sockaddr *)&_servaddr, sizeof(_servaddr)))
	{
		std::cerr << "bind()";
		throw Server::SetupErrorException();
	}
	if (listen(_servFd, 10))
	{
		std::cerr << "listen()";
		throw Server::SetupErrorException();
	}
	memset(&_pollFds, 0, sizeof(_pollFds));
	_pollFds[0].fd = _servFd;
	_pollFds[0].events = POLLIN;
	_pollFds[0].revents = 0;

	signal(SIGINT, Server::sigHandler);
	signal(SIGQUIT, Server::sigHandler);
}

void	Server::sigHandler(int sig)
{
	g_sig = sig;
}

Server::~Server()
{
	if (_servFd > 2)
		close(_servFd);
	for (int i = 0; i < 1024; i++)
	{
		if (_pollFds[i].fd)
			close(_pollFds[i].fd);
	}
	logScript(LOG_END(toString(_servFd)));
}

//getter/setter
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

const mapClient_i_t				&Server::getMapClientsFd(void) const {return (_clientsFd);}

const mapClient_s_t 			&Server::getMapClientsNick(void) const {return (_clientsNick);}



/* ------------------------------------< work in progres >------------------------------------ */

/*      a changer pour envoiler les msg a target et pas le print comme actuellement     */
void	Server::putMsg(const Client& target, const std::string& msg)
{
	std::string output(msg + "\r\n");
	// std::string output(msg);
	if (send(target.getFd(), output.c_str(), output.size(), 0) < 0)
			rmClient(_clientsFd.at(target.getFd()));
}

void	Server::putMsg(const Channel& target, const std::string& msg)
{
	target.log();
	std::string output(msg + "\r\n");
	std::set<int> lst(target.getUser());
	for (std::set<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		if (send(*it, output.c_str(), output.size(), 0) < 0)
			rmClient(_clientsFd.at(*it));
}

//getters/setters
const int	&Server::getPort(void)const
{
	return (_port);
}

struct pollfd		*Server::getPollfds(void)
{
	return (_pollFds);
}

struct pollfd		Server::getPollfds(int  i)
{
	return (_pollFds[i]);
}


const std::string	&Server::getPassword(void)const
{
	return (_password);
}

int	Server::getServFd(void)const
{
	return (_servFd);
}

//exceptions
const char	*Server::SetupErrorException::what()const throw()
{
	return (" error happened during server setup.");
}

//member functions
int	Server::acceptClient(void)
{
	int			clientfd;
	socklen_t	addrsize;
	struct sockaddr_in	clientip;
	
	addrsize = sizeof(clientip);
	clientfd = accept(_servFd, (struct sockaddr *)&clientip, &addrsize);
	if (clientfd == -1)
	{
		std::cout << "client connection failed" << std::endl;
		perror("client");
		return (-1);
	}
	if (fcntl(clientfd, F_SETFL ,O_NONBLOCK))
	{
		std::cout << "client connection failed" << std::endl;
		perror("client");
		return (-1);
	}
	Client	newclient(clientfd, inet_ntoa(clientip.sin_addr));
	_clientsFd.insert(std::make_pair(clientfd, newclient));
	//add clientfd in the pollfd arr.
	for(int i = 0; i < 1023; i++)
	{
		if(!_pollFds[i].fd)
		{
			_pollFds[i].fd = clientfd;
			_pollFds[i].events = POLLIN;
			_pollFds[i].revents = 0;
			break;
		}
	}
	std::cout << "fd " << clientfd << " opened for client" << std::endl;
	logScript(LOG_ACCEPTCLIENT(toString(_servFd), toString(clientfd)));
	return (clientfd);
}

void	Server::rmClient(Client	&client)
{
	
	int			clientFd = client.getFd();
	std::string	clientNick = client.getNickName();
	try
	{
		_clientsNick.erase(clientNick);
		_clientsFd.erase(clientFd);
		_msg.erase(clientFd);
		std::cout << "client " << clientNick << " disconnected" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	for(int i = 0; i < 1023; i++)
	{
		if(_pollFds[i].fd == clientFd)
		{
			_pollFds[i].fd = 0;
			close(clientFd);
			return;
		}
	}
}

void	Server::recieveData(int fd)
{
	char		buff[SIZEBUFF];

	memset(buff, 0, SIZEBUFF);
	if (_msg.find(fd) == _msg.end())
		_msg.insert(std::make_pair(fd, ""));
	std::string &msg = _msg.at(fd);
	int bytes = recv(fd, buff, SIZEBUFF, 0);
	if (bytes == 0)
		return rmClient(_clientsFd.at(fd));
	if (bytes < 0)
		return ;
	msg.append(buff, bytes);
	size_t pos = msg.find("\r\n");
	if (pos != std::string::npos)
	{
		Command::handleCommand((_clientsFd.find(fd))->second, msg.substr(0, pos));
		msg.erase(0, pos + 2);//invalid read 8 after disconnect
	}
}
