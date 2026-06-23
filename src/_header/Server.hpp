
#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class Server
{
	public:
		~Server();
		void							setup			(void);

		void							putMsg			(const Client& target, const std::string& msg);
		void							putMsg			(const Channel& target,const std::string& msg);

		bool 							checkPass		(const std::string pass) 						const;
		bool 							checkClient		(const std::string nick) 						const;
		bool 							checkClient		(const int fd) 									const;

		mapClient_i_t::const_iterator	endClientFd		()												const;
		mapClient_s_t::const_iterator	endClientNick	()												const;
		mapChannel_t::const_iterator	endChannel		()												const;

		int								acceptClient	(void);
		void 							rmClient		(Client &client);
		void							receiveData		(int fd);
			
		void							addClient		(const int fd, Client user);
		void							addClient		(const std::string Name, Client user);
		void							addChannel		(const std::string name, Channel channel);

		//getters/setters
		const int						&getPort		(void)const;
		const std::string				&getPassword	(void)const;
		const std::map<int, Client>			&getMapClientsFd(void)const{return (_clientsFd);}
		const std::map<std::string, Client>	&getMapClientsNick(void)const{return (_clientsNick);}
		struct pollfd					*getPollfds		(void);
		struct pollfd					getPollfds		(int i);
		int								getServFd		(void)const;
	
		mapClient_i_t::iterator			findClient		(const int fd);
		mapClient_s_t::iterator			findClient		(const std::string Name);
		mapChannel_t::iterator			findChannel		(const std::string name);
	
		mapClient_i_t::iterator			beginClientFd	();
		mapClient_s_t::iterator			beginNick		();
		mapChannel_t::iterator			beginChannel	();


		static Server& 					getInstance		(int port = -1, std::string password = "");
		
		static void						sigHandler		(int s);


		class	SetupErrorException : public std::exception
		{
			public:
			virtual const char	*what()const throw();
		};

	private:
		int							_port;
		int							_servfd;
		struct pollfd				_pollfds[1024];
		struct sockaddr_in			_servaddr;
		const std::string			_password;
		mapClient_i_t				_clientsFd;
		mapClient_s_t				_clientsNick;
		mapChannel_t				_channels;

	/*  ------------------< ban >------------------*/

		Server& operator=(const Server &other);

		Server(int port, std::string password);
		Server(const Server &other);

};

#endif