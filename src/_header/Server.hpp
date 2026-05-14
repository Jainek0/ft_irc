
#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

/*  ----------------------- {typedef} -----------------------  */

typedef void (*command_t)(Client&, Cmd&);
typedef std::map<std::string, command_t> mapCommand_t;

typedef std::map<std::string, Channel> mapChannel_t;
typedef mapChannel_t::iterator it_mapChannel_t;

typedef std::map<int, Client> mapClient_i_t;
typedef std::map<std::string, Client> mapClient_s_t;


class Server
{
	public:
		~Server();

		void 						acceptClient	();
		void 						rmClient		(const int fd);
		void 						rmClient		(const std::string str);
		
		
		void						putMsg			(Client target, std::string msg)	const;
		
		bool 						checkClient		(const std::string fd) 				const;
		bool 						checkClient		(const int fd) 						const;

		void						addClient		(const int fd, Client user);
		void						addClient		(const std::string nick, Client user);
		void						addChannel		(const std::string name, Channel channel);

		mapClient_i_t::iterator		findClient		(const int fd);
		mapClient_s_t::iterator		findClient		(const std::string nick);
		mapChannel_t::iterator		findChannel		(const std::string name);

		mapClient_i_t::iterator		endClientFd		();
		mapClient_s_t::iterator		endClientNick	();
		mapChannel_t::iterator		endChannel		();

		mapClient_i_t::iterator		beginClientFd	();
		mapClient_s_t::iterator		beginClientNick	();
		mapChannel_t::iterator		beginChannel	();


		static Server& 				getInstance		(int fd = -1, std::string password = "");
		


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