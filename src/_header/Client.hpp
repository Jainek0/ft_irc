#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "irc.hpp"

class Client
{
	public:
		Client(int fd, std::string ip);
		Client(const Client &other);
		~Client();

		const std::string		getNickName	()			  const;
		const std::string		getUserName	() 			  const;
		const std::string		getPrefix	() 			  const;
		int						getFd		()			  const;
		int						getAuthenti	()			  const;

		void					setNickName	(const std::string);
		void					setUserName	(const std::string);
		void					setAuthenti	(int mod);

		void					addChannel	(const std::string);
		void					rmChannel	(const std::string);
		void					clearChannel();

	private:
		const int 					_fd;
		const std::string 			_ip;
		std::string 			_userName;
		std::string 			_nickName;
		std::set<std::string>	_channels;
		int						_authenticated;

	/*  ------------------< ban >------------------*/
	
		Client& operator=(const Client &other);
};

#endif