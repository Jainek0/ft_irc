#include "../header/Spambot.hpp"
void	Spambot::sa_sig(int sig, siginfo_t info, void *context)
{
	_signal = 0;
}

Spambot::Spambot(int _port, std::string nick, std::string pass) : _signal(1), _port(_port)
{
	struct sigaction	sa;

	sa.sa_sigaction = sa_sig;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	putmsg(_port, "PASS " + pass);
	// check pass error
	putmsg(_port, "NICK " + nick);
	// check nick error
	putmsg(_port, "USER bot");
	vigil();
}

void	Spambot::vigil()
{
	time_t		timecheck;
	struct tm	datetime;
	int			timethen = -1;
	char 		buffer[1024];

	while (_signal){
		timecheck = time(NULL);
		datetime = *localtime(&timecheck);
		recv(socket, buffer, 1024, 0);
		_msg += buffer;
		if (_msg.find('\n'))
		{
			overreact(_msg);
			_msg.clear();
		}
		if(datetime.tm_min != timethen)
		{
			timethen = datetime.tm_min;
			spam();
			//putmsg(_port, "PRIVATEMSG #channel :spamming in progress");
		}	
	}
}

void Spambot::joinChannel(std::string channel)
{
	putmsg(_port, "JOIN #channel");
	putmsg(_port, "PRIVATEMSG #channel :coucou les amis, il faut que je vous parle de ma nouvelle crypto");
}

void Spambot::spam()
{
	if(!_channels.size()>0)
		return ;
	int seed = rand() % 10;
	if (seed == 0)
		putmsg(_port, "PRIVATEMSG #channel :free robux");
	else if (seed == 1)
		putmsg(_port, "PRIVATEMSG #channel :click to get money");
	else if (seed == 2)
		putmsg(_port, "PRIVATEMSG #channel :your computter require an update");
	else if (seed == 3)
		putmsg(_port, "PRIVATEMSG #channel :turning on your camera");
	else if (seed == 4)
		putmsg(_port, "PRIVATEMSG #channel :you have been hacked");
	else if (seed == 5)
		putmsg(_port, "PRIVATEMSG #channel :your mama");
	else if (seed == 6)
		putmsg(_port, "PRIVATEMSG #channel :how to lose fat easily, doctor hate this");
	else if (seed == 7)
		putmsg(_port, "PRIVATEMSG #channel :babes in your area");
	else if (seed == 8)
		putmsg(_port, "PRIVATEMSG #channel :try this new mobile game");
	else if (seed == 9)
		putmsg(_port, "PRIVATEMSG #channel :nobody loves you");
}

void Spambot::overreact(std::string msg)
{
	if(!_channels.size()>0)
		return ;
	
	std::map<std::string, std::string> shout;
	shout.insert("pile", "macron explosion face");
	shout.insert("face", "macron dec		std::set<std::string>	_channels;apitation pile");
	std::ostringstream os(_msg);
	for (std::string str << os; str; str << os)
	{
		box::iterator it shout.find(str);
		if (it != shout.end()) {
			putmsg(it->second);
		}
	}
}
