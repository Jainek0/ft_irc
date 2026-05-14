#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "irc.hpp"

class Client
{
	public:
		Client(int fd);
		Client(const Client &other);
		~Client();

		const std::string	getUsername()	const;
		const std::string	getNick() 		const;
		int					fd()			const;

		void				setUsername(const std::string);
		void				setNick(const std::string);
		
	private:
		const int 			_fd;
		std::string 		_nick;
		std::string 		_username;
		
	/*  ------------------< ban >------------------*/
	
		Client& operator=(const Client &other);
};

#endif