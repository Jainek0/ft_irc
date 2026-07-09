#include "../header/Spambot.hpp"

void	Spambot::sa_sig(int sig, siginfo_t info, void *context)
{
	_signal = 0;
}

bool	Spambot::getSignal() {return _signal;}

int	Spambot::receiveData()
{
	char				buff[SIZEBUFF];
	static std::string	msg;

	memset(buff, 0, SIZEBUFF);
	int	bytes = recv(_port, buff, SIZEBUFF, 0);
	if (bytes == 0)
		return (1);
	if (bytes < 0)
		return (0);
	msg.append(buff, bytes);
	size_t	pos;
	while ((pos = msg.find("\r\n")) != std::string::npos)
	{
		Cmd	cmd(msg.substr(0, pos));
		botHandle(cmd);
		msg.erase(0, pos + 2);
	}
	return(0);
}

void	Spambot::kickCheck(Cmd cmd)
{
	if (cmd.command() == "KICK")
	{
		if (cmd.arg(0) == _nick)
			_channels.erase(cmd.arg(1));
	}
}

void	Spambot::addCheck(Cmd cmd)
{
	if(cmd.command() == "JOIN")
	{
		putMsg("PRIVATEMSG #" + cmd.arg(0) + " :coucou les amis, il faut que je vous parle de ma nouvelle crypto");
		_channels.insert(cmd.arg(0));
	}
}

void	Spambot::spamming()
{
	if(!_channels.size()>0)
		return ;
	int rng = rand() % 10;
	if (rng == 0)
		putMsg("PRIVATEMSG #channel :free robux");
	else if (rng == 1)
		putMsg("PRIVATEMSG #channel :click to get money");
	else if (rng == 2)
		putMsg("PRIVATEMSG #channel :your computter require an update");
	else if (rng == 3)
		putMsg("PRIVATEMSG #channel :turning on your camera");
	else if (rng == 4)
		putMsg("PRIVATEMSG #channel :you have been hacked");
	else if (rng == 5)
		putMsg("PRIVATEMSG #channel :your mama");
	else if (rng == 6)
		putMsg("PRIVATEMSG #channel :how to lose fat easily, doctor hate this");
	else if (rng == 7)
		putMsg("PRIVATEMSG #channel :babes in your area");
	else if (rng == 8)
		putMsg("PRIVATEMSG #channel :try this new mobile game");
	else if (rng == 9)
		putMsg("PRIVATEMSG #channel :nobody loves you");
}

void	Spambot::overReact(Cmd cmd)
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
	// 		putMsg(it->second);
	// 	}
	// }
}

void	Spambot::inviteCheck(Cmd cmd)
{
	if(cmd.command() == "INVITE")
	{
		if(cmd.arg(0) == _nick)
			putMsg("JOIN #" + cmd.arg(1));
	}
}

void	Spambot::botHandle(Cmd cmd)
{
	if (cmd.command() == "451")
		endBot();
	if (cmd.prefix() == _nick + "!bot@127.0.0.1")
		addCheck(cmd);
	else
	{
		inviteCheck(cmd);
		kickCheck(cmd);
		overReact(cmd);
	}
	// invite function "INVITE #<channel>"
	// 	->joinChannel(<channel>);
	// if added to a channel
	// 	->addChannel();
	// if(kickChecker())
	// 	->botLeave
	// react function "PRIVATEMSG #<channel> :<message>"

	// check that i am not alone in the channel
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
			//putMsg(_port, "PRIVATEMSG #channel :spamming in progress");
		}	
	}
}

void	Spambot::putMsg(const std::string& msg)
{
	std::string output(msg + "\r\n");
	if (send(_port, output.c_str(), output.size(), 0) < 0)
			endBot();
}

void	Spambot::endBot()
{
	_signal = 0;
}


Spambot::Spambot(int _port, std::string nick, std::string pass) : _signal(1), _port(_port)
{
	struct sigaction	sa;

	sa.sa_sigaction = sa_sig;
	sa.sa_flags = SA_SIGINFO;
	_signal = 1;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	putMsg("PASS " + pass);
	putMsg("NICK " + nick);
	putMsg("USER bot");
	vigil(); // ?
}