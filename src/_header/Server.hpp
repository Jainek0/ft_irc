
#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class Server
{
	public:
		~Server();
		void							setup			(void);

		void							putMsg			(const Client& target, const std::string& msg)	const;
		void							putMsg			(const Channel& target,const std::string& msg)	const;

		
		bool 							checkPass		(const std::string pass) 						const;
		bool 							checkClient		(const std::string nick) 						const;
		bool 							checkClient		(const int fd) 									const;

		mapClient_i_t::const_iterator	endClientFd		()												const;
		mapClient_s_t::const_iterator	endClientNick	()												const;
		mapChannel_t::const_iterator	endChannel		()												const;

		void 							acceptClient	(void);
		void 							rmClient		(const int fd);
		void 							rmClient		(const std::string str);
		void							recieveData		(int fd);
			
		void							addClient		(const int fd, Client user);
		void							addClient		(const std::string Name, Client user);
		void							addChannel		(const std::string name, Channel channel);

		//getters/setters
		const int						&getPort		(void)const;
		const std::string				&getPassword	(void)const;
		const std::map<int, Client>			&getMapClientsFd(void)const{return (_mapClientsFd);}
		const std::map<std::string, Client>	&getMapClientsNick(void)const{return (_mapClientsNick);}
		struct pollfd					*getPollfds		(void);
		struct pollfd					getPollfds		(int i);
		int								getServFd		(void)const;
	
		mapClient_i_t::iterator			findClient		(const int fd);
		mapClient_s_t::iterator			findClient		(const std::string Name);
		mapChannel_t::iterator			findChannel		(const std::string name);
	
		mapClient_i_t::iterator			beginClientFd	();
		mapClient_s_t::iterator			beginNick		();
		mapChannel_t::iterator			beginChannel	();


		static Server& 					getInstance		(int fd = -1, std::string password = "");
		

		class	SetupErrorException : public std::exception
		{
			public:
			virtual const char	*what()const throw();
		};

	private:
		int							_servfd;
		struct pollfd				_pollfds[1024];
		int 						_port;//double. might be useful.
		struct sockaddr_in			_servaddr;
		const std::string			_password;
		mapClient_i_t				_clientsFd;
		mapClient_s_t				_clientsNick;
		mapChannel_t				_channels;

	/*  ------------------< ban >------------------*/

		Server& operator=(const Server &other);

		Server(int fd, std::string password);
		Server(const Server &other);

};

#endif