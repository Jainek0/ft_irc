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

# include <poll.h>//poll
# include <fcntl.h>//fcntl

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

		void loop();

		void receiveData();

		void botHandle(Cmd cmd);

		void inviteCheck(Cmd cmd);

		void addCheck(Cmd cmd);

		void kickCheck(Cmd cmd);

		void endBot();

		void loopChannel(std::string msg);

		void spamming();

		void overReact(Cmd cmd);

		void addBuffOut(const std::string&);

		static void sa_sig(int sig);

		bool initSocket();

		bool getSignal();

	private:
		static volatile sig_atomic_t 	_signal;

		int 							_port;
		int 							_socket;
		std::set<std::string>			_channels;
		std::string						_msg;
		std::string						_nick;
		std::string						_prefix;
		struct pollfd					_pollFd;
		std::string						_buffOut;

		Spambot(Spambot &other);
		Spambot& operator=(Spambot &other);
};

#endif
