#ifndef SPAMBOT_HPP
# define SPAMBOT_HPP

# include "irc.hpp"
# include <chrono>
# include <thread>
# include <ctime>
# include <iostream>
# include <istream>
# include <signal.h>

typedef std::map<std::string, std::string> box;

class Spambot
{
	public:
		//constructor/destructor
		Spambot(int port, std::string nick, std::string pass);
		Spambot(Spambot &other);
		Spambot& operator=(Spambot &other);
		~Spambot();



		void vigil();

		void joinChannel(std::string channel);

		void spam();

		void overreact();

		//getters/setters
		// const std::string	&getNickname(void)const {return(_nick);}
		// void				setNickname(std::string nick) {_nick = nick;}

	private:
		void					sa_sig(int sig, siginfo_t info, void *context);
		int 					_port;
		std::set<std::string>	_channels;
		std::string				_msg;

		bool					_signal;

};

#endif
