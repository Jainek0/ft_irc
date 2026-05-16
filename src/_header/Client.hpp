#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "irc.hpp"

class Client
{
	public:
		Client(int fd);
		Client(const Client &other);
		~Client();

		const std::string	getNickName	()			  const;
		const std::string	getUserName	() 			  const;
		const std::string	getPrefix	() 			  const;
		int					getFd		()			  const;

		void				setNickName	(const std::string);
		void				setUserName	(const std::string);
		
	private:
		const int 			_fd;
		std::string 		_userName;
		std::string 		_nickName;
		
	/*  ------------------< ban >------------------*/
	
		Client& operator=(const Client &other);
};

#endif