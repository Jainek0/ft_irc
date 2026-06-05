
#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class Server
{
	public:
		//constructor/destructor
		~Server();
		static Server&	getInstance(int fd = -1, std::string password = ""){
			static Server server(fd, password);
			return server;}

		//getters/setters
		const int			&getPort(void)const;
		const std::string	&getPassword(void)const;
		const std::map<int, Client>			&getMapClientsFd(void)const{return (_mapClientsFd);}
		const std::map<std::string, Client>	&getMapClientsNick(void)const{return (_mapClientsNick);}
		//	&getChannels(void)const;
		struct pollfd		*getPollfds(void);
		struct pollfd		getPollfds(int i);
		int					getServFd(void)const;
		void	setPort(const int &port);
		void	setPassword(const std::string &password);
		
		//member functions
		void	setup(void);
		int		acceptClient(void);
		void	removeClient(Client &client);
		void	recieveData(int fd);
		void	addChannel(const std::string name, Channel channel);
		void	handleCommand(int fd, std::string cmd);

		class	SetupErrorException : public std::exception
		{
			public:
			virtual const char	*what()const throw();
		};
			
	private:
		int					_servfd;
		struct pollfd		_pollfds[1024];
		int 				_port;//doublon. might be useful.
		struct sockaddr_in	_servaddr;
		std::string			_password;
		std::map<int, Client>			_mapClientsFd;
		std::map<std::string, Client>	_mapClientsNick;
		std::map<std::string, Channel>	_channels;

		//---------------------------------------//
		Server(int port, std::string password);
		Server(Server &other);
		Server& operator=(const Server &other);
};

#endif
