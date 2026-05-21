#include "_header/irc.hpp"

//constructor/destructor
void	Server::setup(void)
{
	_servfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_servfd == -1)
	{
		std::cout << "socket()";
		throw Server::SetupErrorException();
	}
	//if (setsockopt(SO_REUSEADDR));??
	//if (fcntl(O_NONBLOCK));??

	//vv set values in the sockaddr struct vv
	_servaddr.sin_family = AF_INET;
	_servaddr.sin_port = htons(_port);
	inet_pton(AF_INET, "127.0.0.1", &(_servaddr.sin_addr));

	if (bind(_servfd, (struct sockaddr *)&_servaddr, sizeof(_servaddr)))
	{
		std::cout << "bind()";
		throw Server::SetupErrorException();
	}
	if (listen(_servfd, 10))
	{
		std::cout << "listen()";
		throw Server::SetupErrorException();
	}
	for(int i = 0; i < 1023; i++)
	{
		if(!_pollfds[i].fd)
		{
			_pollfds[i].fd = _servfd;
			//setup event & revent;
			break;
		}
	}
	memset(&_pollfds, 0, sizeof(_pollfds));
	_pollfds[0].fd = _servfd;
}

Server::Server(int port, std::string password): _port(port), _password(password)
{}
//^^^setup fct à part pour pouvoir try/catch dans main?^^^

Server::Server(Server &og)
{
	*this = og;
}

Server::~Server(void)
{
	std::cout << "Server destroyed" << std::endl;
}

//operator overload
Server	&Server::operator=(const Server &og)
{
	//!\close og?
	_servfd = og._servfd;
	_port = og._port;
	//servaddr struct = ...
	_password = og._password;
	// _clientsFd = og._clientsFd;//instantiation issue
	// _clientsNick = og._clientsNick;//instantiation issue
	// _channels = og._channels;//instantiation issue
	return (*this);
}

//getters/setters
const int	&Server::getPort(void)const
{
	return (_port);
}

struct pollfd		*Server::getPollfds(void)
{
	return (_pollfds);
}

struct pollfd		Server::getPollfds(int  i)
{
	return (_pollfds[i]);
}


const std::string	&Server::getPassword(void)const
{
	return (_password);
}

// const std::map	&Server::getClients(void)const
// {
// 	return (_clients);
// }

// const std::map	&Server::getChannels(void)const
// {
// 	return (_channels);
// }

void	Server::setPort(const int &port)
{
	_port = port;
}

void	Server::setPassword(const std::string &password)
{
	_password = password;
}

int	Server::getServFd(void)const
{
	return (_servfd);
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

	addrsize = sizeof(_servaddr);
	clientfd = accept(_servfd, (struct sockaddr *)&_servaddr, &addrsize);
	if (clientfd == -1)
	{
		std::cout << "client connection failed" << std::endl;
		perror("client");
		return (-1);
	}
	std::cout << "fd " << clientfd << " opened for client" << std::endl;
	//add clientfd in the pollfd arr.
	for(int i = 0; i < 1023; i++)
	{
		if(!_pollfds[i].fd)
		{
			_pollfds[i].fd = clientfd;
			//setup event & revent;
			break;
		}
	}
	_clientsFd.insert(std::make_pair(clientfd, Client(clientfd)));
	return (clientfd);
}

void	Server::removeClient(Client	&client)
{
	_clientsFd.erase(client.getFd());
	_clientsNick.erase(client.getNick());

	int	clientfd = client.getFd();
	for(int i = 0; i > 1023; i++)
	{
		if(_pollfds[i].fd == clientfd)
		{
			_pollfds[i].fd = 0;
			close(clientfd);
			//client.~Client();??
			return;
		}
	}
}

void	Server::recieveData(int fd)
{
	(void)fd;
	// recv(fd, buff, buffsize);
	//parse();
}

void	Server::addChannel(const std::string name, Channel channel)
{
	(void)name;
	(void)channel;
}

// void	Server::handleCommand(int fd, std::string cmd)
// {

// }
