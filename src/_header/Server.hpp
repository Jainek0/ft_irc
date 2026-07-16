
#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class Server
{
	public:
		~Server();
		void								setup					();

		int									loop					();

		void								addBuffOut				(const Client& target, const std::string& msg);
		void								addBuffOut				(const Channel& target, const std::string& msg);
		void								addBuffOut				(const Channel& target, const Client& user,const std::string& msg);

		bool 								checkPass				(const std::string pass) 						const;
		bool 								checkClient				(const std::string nick) 						const;
		bool 								checkClient				(const int fd) 									const;

		mapClient_t::const_iterator			endClientFd				()												const;
		mapNick_t::const_iterator			endNicks				()												const;
		mapChannel_t::const_iterator		endChannel				()												const;

		int									acceptClient			();
		void 								rmClient				(Client &client);
		void 								rmNick					(const std::string nickName);
		void 								rmChannel				(const std::string name);
		void								recieveData				(int fd);

		void								addClient				(const int fd, Client user);
		void								addNick					(const std::string Name, const int);
		void								addChannel				(const std::string name, Channel channel);

		//getters/setters	
		const int							&getPort				()												const;
		const std::string					&getPassword			()												const;
		const mapClient_t					&getMapClientsFd		()												const;
		const mapNick_t						&getMapClientsNick		()												const;
		int									getServFd				()												const;
		struct pollfd						*getPollfds				();
		struct pollfd						getPollfds				(int i);

		mapClient_t::iterator				findClient				(const int fd);
		mapClient_t::iterator				findClient				(const std::string Name);
		mapChannel_t::iterator				findChannel				(const std::string name);

		mapClient_t::iterator				beginClientFd			();
		mapNick_t::iterator					beginNick				();
		mapChannel_t::iterator				beginChannel			();


		static Server& 						getInstance				(int port = -1, std::string password = "");

		static void							sigHandler				(int s);


		class	SetupErrorException : public std::exception
		{
			public:
			virtual const char	*what()const throw();
		};

	private:
		int							_port;
		int							_servFd;
		struct pollfd				_pollFds[1024];
		struct sockaddr_in			_servaddr;
		const std::string			_password;
		mapClient_t					_clientsFd;
		mapNick_t					_nicks;
		mapChannel_t				_channels;
		std::map<int, std::string>	_buffOut;
		std::map<int, std::string>	_buffIn;

	/*  ------------------< ban >------------------*/

		Server& operator=(const Server &other);

		Server(int port, std::string password);
		Server(const Server &other);

};

#endif