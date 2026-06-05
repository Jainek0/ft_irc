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

		//getters/setters
		const int			&getFd(void)const{return (_fd);}
		const std::string	&getNickname(void)const{return(_nick);}
		void	setNickname(std::string nick){_nick = nick;}
		void	setUsername(std::string username){_username = username;}
		bool					getAuthenti	()const{return(_authenticated);}
		void					setAuthenti	(){_authenticated = 1;}
		void					setFd(int fd){_fd = fd;}
		void					setIp(std::string ip){_ip = ip;}

	private:
		int 			_fd;
		std::string 	_ip;
		std::string 	_nick;
		std::string 	_username;
		bool 			_authenticated;
};

#endif