#include "../header/Spambot.hpp"

void	Spambot::sa_sig(int sig, siginfo_t info, void *context)
{
	_signal = 0;
}

void	Spambot::receiveData()
{
	char		buff[SIZEBUFF];

	memset(buff, 0, SIZEBUFF);
	static std::string	msg;
	int bytes = recv(_port, buff, SIZEBUFF, 0);
	if (bytes == 0)
		return ;
	msg.append(buff, bytes);
	size_t pos = msg.find("\r\n");
	if (pos != std::string::npos)
	{
		botHandle(msg.substr(0, pos));
		msg.erase(0, pos + 2);
	}
}

void	Spambot::kickCheck(std::set<std::string> split)
{
	if (split[0] = "KICK")
	{
		if (isChannel(split[1]))
		{
			if (split[2] == Spambot.nick)
				botLeave(split[1]);
		}
	}

}

void	Spambot::addCheck(std::set<std::string> split)
{
	if()
	{
		if()
		{
			putmsg(_port, "PRIVATEMSG #channel :coucou les amis, il faut que je vous parle de ma nouvelle crypto");
			// add the channel to _channels
		}
	}
}

void	Spambot::botLeave(std::string channel)
{
	if (isChannel(channel))
	{
		
	}
	// check that i have left a channel
	// substract from _channels
}

void	Spambot::spamming()
{
	if(!_channels.size()>0)
		return ;
	int rng = rand() % 10;
	if (rng == 0)
		putmsg(_port, "PRIVATEMSG #channel :free robux");
	else if (rng == 1)
		putmsg(_port, "PRIVATEMSG #channel :click to get money");
	else if (rng == 2)
		putmsg(_port, "PRIVATEMSG #channel :your computter require an update");
	else if (rng == 3)
		putmsg(_port, "PRIVATEMSG #channel :turning on your camera");
	else if (rng == 4)
		putmsg(_port, "PRIVATEMSG #channel :you have been hacked");
	else if (rng == 5)
		putmsg(_port, "PRIVATEMSG #channel :your mama");
	else if (rng == 6)
		putmsg(_port, "PRIVATEMSG #channel :how to lose fat easily, doctor hate this");
	else if (rng == 7)
		putmsg(_port, "PRIVATEMSG #channel :babes in your area");
	else if (rng == 8)
		putmsg(_port, "PRIVATEMSG #channel :try this new mobile game");
	else if (rng == 9)
		putmsg(_port, "PRIVATEMSG #channel :nobody loves you");
}

void	Spambot::overReact(std::string msg)
{
	// if(!_channels.size()>0)
	// 	return ;
	
	// std::map<std::string, std::string> shout;
	// shout.insert("pile", "macron explosion face");
	// shout.insert("face", "macron decapitation pile");
	// std::ostringstream os(_msg);
	// for (std::string str << os; str; str << os)
	// {
	// 	box::iterator it shout.find(str);
	// 	if (it != shout.end()) {
	// 		putmsg(it->second);
	// 	}
	// }
}

int	isChannel(std::string channel)
{

	return (0);
}

void	Spambot::inviteCheck(std::set<std::string> split)
{
	if(split[0] == "INVITE")
	{
		if(isChannel(split[1]))
		{
			if(split[2] == Spambot.nick)
				putmsg(_port, "JOIN #<channel>");
		}
	}
}

void	Spambot::botHandle(std::string msg)
{
	std::set<std::string> split = (msg);
	inviteCheck(split);
	addCheck(split);
	kickCheck(msg);
	overReact(msg);
	// invite function "INVITE #<channel>"
	// 	->joinChannel(<channel>);
	// if added to a channel
	// 	->addChannel();
	// if(kickChecker())
	// 	->botLeave
	// react function "PRIVATEMSG #<channel> :<message>"

	check that i am not alone in the channel
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
		// recv(socket, buffer, 1024, 0);
		receiveData();
		_msg += buffer;
		if (_msg.find('\n'))
		{
			botHandle(_msg);
			_msg.clear();
		}
		if(datetime.tm_min != timethen)
		{
			timethen = datetime.tm_min;
			spamming();
			//putmsg(_port, "PRIVATEMSG #channel :spamming in progress");
		}	
	}
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