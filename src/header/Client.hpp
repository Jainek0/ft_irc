#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

class Client
{
	public:
		Client(int fd, std::string nick, std::string username);
		Client(const Client &other);
		~Client();

		const std::string	getUsername()	const;
		const std::string	nick() 			const;
		int					fd()			const;

		void				setUsername(const std::string);
		
	private:
		const int 			_fd;
		const std::string 	_nick;
		std::string 		_username;
		
	/*  ------------------< ban >------------------*/
	
		Client& operator=(const Client &other);
};

#endif