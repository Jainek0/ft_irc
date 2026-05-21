#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "irc.hpp"

class Client
{
	public:
		//constructor/destructor
		Client(int fd);
		Client(Client &other);
		Client& operator=(Client &other);
		~Client();

	private:
		int 			_fd;
		std::string 	_ip;
		std::string 	_nick;
		std::string 	_username;
		bool 			_authenticated;
};

#endif