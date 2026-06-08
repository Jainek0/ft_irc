#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "irc.hpp"

class Client
{
	public:
		Client(int fd);
		Client(const Client &other);
		~Client();

		const std::string		getNickName	()			  const;
		const std::string		getUserName	() 			  const;
		const std::string		getPrefix	() 			  const;
		int						getFd		()			  const;
		bool					getAuthenti	()			  const;

		void					setNickName	(const std::string);
		void					setUserName	(const std::string);
		void					setAuthenti	();

		void					addChannel	(const std::string);
		void					rmChannel	(const std::string);
		void					clearChannel();


		void					setFd(int fd)			{_fd = fd;}
		void					setIp(std::string ip)	{_ip = ip;}

		
	private:
		const int 				_fd;
		std::string 			_ip;
		std::string 			_userName;
		std::string 			_nickName;
		std::set<std::string>	_channels;
		bool					_authenticated;

		
	/*  ------------------< ban >------------------*/
	
		Client& operator=(const Client &other);
};

#endif