#ifndef SPAMBOT_HPP
# define SPAMBOT_HPP

# include "irc.hpp"
# include <chrono>
# include <thread>
# include <ctime>

class Spambot
{
	public:
		//constructor/destructor
		Spambot();
		Spambot(Spambot &other);
		Spambot& operator=(Spambot &other);
		~Spambot();

		void joinChannel(std::string channel);
		{
			putmsg(fdServ, "JOIN #channel");
			putmsg(fdServ, "PRIVATEMSG #channel :coucou les amis, il faut que je vous parle de ma nouvelle crypto");
		}
		void spam();
		{
			while(react == 0)
			{

				putmsg(fdServ, "PRIVATEMSG #channel :buy my robux");
			}
		}
		typedef std::map<std::string, std::string> box;
		void overreact(std::string msg);
		{
			std::map<std::string, std::string> shout;
			shout.insert("pile", "macron explosion face");
			shout.insert("face", "macron decapitation pile");
			std::ostringstream os(msg);
			for (std::string str << os; str; str << os)
			{
				box::iterator it shout.find(str);
				if (it != shout.end()) {
					putmsg(it->second);

				}
			}
		}
		
		//getters/setters
		const std::string	&getNickname(void)const {return(_nick);}
		void				setNickname(std::string nick) {_nick = nick;}
		
	private:
		int 			_fd;
		std::string 	_nick;
};

#endif
