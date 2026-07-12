#ifndef SPAMBOT_HPP
# define SPAMBOT_HPP

# include <ctime>
# include <cstdlib>
# include <iostream>
# include <istream>
# include <signal.h>
# include <map>
# include <set>
# include <vector>
# include <sys/socket.h>
# include <sstream>
# include <cstring>

#include <arpa/inet.h>

# include "Cmd.hpp"

# define SIZEBUFF 1024
typedef std::map<std::string, std::string> box;

class Spambot
{
	public:
		//constructor/destructor
		Spambot(int port, std::string nick, std::string pass);

		~Spambot();

		void vigil();

		int	receiveData();

		void botHandle(Cmd cmd);

		void joinChannel(std::string channel);

		void inviteCheck(Cmd cmd);

		void addCheck(Cmd cmd);

		void kickCheck(Cmd cmd);

		void endBot();

		// void botLeave(std::string channel);

		void loopChannel(std::string msg);
		void spamming();

		void overReact(Cmd cmd);

		void putMsg(const std::string&);

		static void sa_sig(int sig);

		bool initSocket();

		//getters/setters
		// const std::string	&getNickname(void)const {return(_nick);}
		// void				setNickname(std::string nick) {_nick = nick;}

		bool	getSignal();

	private:
		static volatile sig_atomic_t 	_signal;

		int 							_port;
		int 							_socket;
		std::set<std::string>			_channels;
		std::string						_msg;
		std::string						_nick;
		std::string						_prefix;

		Spambot(Spambot &other);
		Spambot& operator=(Spambot &other);
};

#endif
