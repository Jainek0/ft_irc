
#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class Server
{
	public:
		~Server();

		void							putMsg			(const Client& target, const std::string& msg)	const;
		void							putMsg			(const Channel& target,const std::string& msg)	const;

		
		bool 							checkPass		(const std::string pass) 						const;
		bool 							checkClient		(const std::string nick) 						const;
		bool 							checkClient		(const int fd) 									const;

		mapClient_i_t::const_iterator	endClientFd		()												const;
		mapClient_s_t::const_iterator	endClientNick	()												const;
		mapChannel_t::const_iterator	endChannel		()												const;

		void 							acceptClient	();
		void 							rmClient		(const int fd);
		void 							rmClient		(const std::string str);
			
		void							addClient		(const int fd, Client user);
		void							addClient		(const std::string Name, Client user);
		void							addChannel		(const std::string name, Channel channel);
	
		mapClient_i_t::iterator			findClient		(const int fd);
		mapClient_s_t::iterator			findClient		(const std::string Name);
		mapChannel_t::iterator			findChannel		(const std::string name);
	
		mapClient_i_t::iterator			beginClientFd	();
		mapClient_s_t::iterator			beginNick		();
		mapChannel_t::iterator			beginChannel	();


		static Server& 					getInstance		(int fd = -1, std::string password = "");
		


	private:
		const int					_fd;
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