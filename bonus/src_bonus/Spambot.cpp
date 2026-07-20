#include "../header_bonus/Spambot.hpp"

volatile sig_atomic_t Spambot::_signal = 1;

void Spambot::sa_sig(int sig)
{
    (void)sig;
    _signal = 0;
}

bool	Spambot::getSignal() {return _signal;}

void	Spambot::receiveData()
{
	char				buff[SIZEBUFF];
	static std::string	msg;

	memset(buff, 0, SIZEBUFF);
	int	bytes = recv(_socket, buff, SIZEBUFF, 0);
	if (bytes > 0)
		std::cout << buff << std::endl;
	if (bytes == 0)
		endBot();
	if (bytes < 0)
		return ;
	msg.append(buff, bytes);
	size_t	pos;
	while ((pos = msg.find("\r\n")) != std::string::npos)
	{
		Cmd	cmd(msg.substr(0, pos));
		botHandle(cmd);
		msg.erase(0, pos + 2);
	}
}

void	Spambot::kickCheck(Cmd cmd)
{
	if (cmd.command() == "441")
	{
		_channels.erase(cmd.arg(1));
	}
}

void	Spambot::addCheck(Cmd cmd)
{
	if(cmd.command() == "JOIN")
	{
		std::cout << "privmsg in to " << cmd.arg(0) << std::endl;
		addBuffOut("PRIVMSG " + cmd.arg(0) + " :Hello World");
		_channels.insert(cmd.arg(0));
	}
}

void Spambot::loopChannel(std::string msg)
{
	for (std::set<std::string>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		addBuffOut("PRIVMSG " + *it + " " + msg);
	}
}

void	Spambot::spamming()
{
	if(_channels.size() == 0)
		return ;
	int rng = rand() % 10;
	if (rng == 0)
		loopChannel(":free robux");
	else if (rng == 1)
		loopChannel(":click to get your prize money");
	else if (rng == 2)
		loopChannel(":your computer require an update");
	else if (rng == 3)
		loopChannel(":turning on your camera");
	else if (rng == 4)
		loopChannel(":you have been hacked");
	else if (rng == 5)
		loopChannel(":your ugly mama");
	else if (rng == 6)
		loopChannel(":how to lose fat easily, doctors hate this");
	else if (rng == 7)
		loopChannel(":babes in your area");
	else if (rng == 8)
		loopChannel(":try this new mobile game");
	else if (rng == 9)
		loopChannel(":nobody loves you");
}

void	Spambot::overReact(Cmd cmd)
{
	if(_channels.size() == 0)
		return ;
	
	if (cmd.command() == "MODE")
	{
		if (cmd.arg(1).find("+o") != std::string::npos && cmd.arg(2).find(_nick) != std::string::npos)
		{
			addBuffOut("PRIVMSG " + cmd.arg(0) + " :i'm a coward");
			_channels.erase(cmd.arg(0));
			return addBuffOut("PART " + cmd.arg(0));
		}
	}

	if (cmd.command() == "PRIVMSG")
	{
		std::cout << "overReact" << std::endl;
		if (cmd.argcs(1).find("test") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :want to test me ?");
		else if (cmd.argcs(1).find("yes") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :no");
		else if (cmd.argcs(1).find("no") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :yes");
		else if (cmd.argcs(1).find("67") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :six seven !!!");
		else if (cmd.argcs(1).find("bot") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :and we are legion");
		else if (cmd.argcs(1).find("left") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :right");
		else if (cmd.argcs(1).find("right") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :left");
		else if (cmd.argcs(1).find("up") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :down");
		else if (cmd.argcs(1).find("down") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :up");
		else if (cmd.argcs(1).find("hello") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :goodbye");
		else if (cmd.argcs(1).find("lol") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :you suck");
		else if (cmd.argcs(1).find("one piece") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :luffy is cringe");
		else if (cmd.argcs(1).find("kroussar") != std::string::npos)
			return addBuffOut("PRIVMSG " + cmd.arg(0) + " :le goat");
		else 
			std::cout << "no overReact" << std::endl;

	}
}

void	Spambot::inviteCheck(Cmd cmd)
{
	if(cmd.command() == "INVITE")
	{
		std::cout << "INVITE " << cmd.arg(1) << std::endl;
		if(cmd.arg(0) == _nick)
			addBuffOut("JOIN " + cmd.arg(1));
		_channels.insert(cmd.arg(1));
	}
}

void	Spambot::botHandle(Cmd cmd)
{
	std::cout << cmd.command() << std::endl;
	if (cmd.command() == "433")
		endBot();
	if (cmd.command() == "451")
		endBot();
	if (cmd.command() == "464")
		endBot();
	if (":" + cmd.prefix() == _prefix)
		addCheck(cmd);
	else
	{
		inviteCheck(cmd);
		kickCheck(cmd);
		overReact(cmd);
	}
}

void Spambot::loop()
{
    std::time_t timecheck;
    std::tm*    datetime;
    int         timethen = -1;

    while (_signal)
    {
		int	retpoll = poll(&_pollFd, 1, 1000);
		if (retpoll == -1)
		{
			std::cerr << "poll error" << std::endl;
			return ;
		}
        timecheck = std::time(NULL);
        datetime = std::localtime(&timecheck);

		if ((_pollFd).revents & POLLIN)
		{
			std::cout << " POLLIN" << std::endl;
			receiveData();
		}
		if ((_pollFd).revents & POLLOUT)
		{
			std::cout << " POLLOUT" << std::endl;
			if (!_buffOut.empty())
			{
				ssize_t bytes = send(_socket, _buffOut.c_str(), _buffOut.size(), 0);
				if (bytes < 0)
					endBot();
				else
					_buffOut.erase(0, bytes);
				if (_buffOut.empty())
					_pollFd.events = POLLIN;
			}
		}

        if (datetime && datetime->tm_min != timethen)
        {
			std::cout << "spam" << std::endl;
            timethen = datetime->tm_min;
            spamming();
        }
    }
}

void Spambot::addBuffOut(const std::string &msg)
{
	_buffOut += msg + "\r\n";
	_pollFd.events = POLLIN | POLLOUT;
}

void	Spambot::endBot()
{
	_signal = 0;
}

Spambot::Spambot(int port, std::string nick, std::string pass)
    : _port(port), _socket(-1), _nick(nick),
      _prefix(":" + nick + "!bot@127.0.0.1")
{

    if (initSocket())
    {
        endBot();
        return;
    }

    addBuffOut("PASS " + pass);
    addBuffOut("NICK " + nick);
    addBuffOut("USER bot");
}

bool Spambot::initSocket()
{
	_socket  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == -1)
	{
		std::cerr << "socket()";
		return true;
	}

	if (fcntl(_socket, F_SETFL, O_NONBLOCK))
	{
		std::cerr << "fcntl()";
		return true;
	}

	int opt = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

	struct sockaddr_in 	servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(_port);

	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

	connect(_socket, (sockaddr *)&servaddr, sizeof(servaddr));
	memset(&_pollFd, 0, sizeof(_pollFd));
	_pollFd.fd = _socket;
	_pollFd.events = POLLIN;
	_pollFd.revents = 0;

	signal(SIGINT, sa_sig);
	signal(SIGQUIT, sa_sig);
	return false;
}


Spambot::~Spambot()
{
    if (_socket != -1)
	{
        if (close(_socket))
			std::cout << "close socket" << std::endl;
	}
	std::cout << "am dead\n";
}