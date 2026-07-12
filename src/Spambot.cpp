#include "../header/Spambot.hpp"

volatile sig_atomic_t Spambot::_signal = 1;

void Spambot::sa_sig(int sig)
{
    (void)sig;
    _signal = 0;
}

bool	Spambot::getSignal() {return _signal;}

int	Spambot::receiveData()
{
	char				buff[SIZEBUFF];
	static std::string	msg;
	
	// std::cout << "read" << std::endl;
	memset(buff, 0, SIZEBUFF);
	int	bytes = recv(_socket, buff, SIZEBUFF, 0);
	if (bytes > 0)
		std::cout << buff << std::endl;
	if (bytes == 0)
		return (1);
	if (bytes < 0)
		return (0);
	msg.append(buff, bytes);
	size_t	pos;
	while ((pos = msg.find("\r\n")) != std::string::npos)
	{
		Cmd	cmd(msg.substr(0, pos));

		// std::cout << "PREFIX = [" << cmd.prefix() << "]\n"; // test
		// std::cout << "COMMAND = [" << cmd.command() << "]\n";

		// for (size_t i = 0; i < cmd.sizeArgs(); ++i)
		// 	std::cout << "ARG " << i << " = [" << cmd.arg(i) << "]\n"; // test

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
		std::cout << "privmsg in to " << cmd.arg(0) << std::endl;
		putMsg(_prefix + " PRIVMSG " + cmd.arg(0) + " :coucou les amis, il faut que je vous parle de ma nouvelle crypto");
		_channels.insert(cmd.arg(0));
	}
}

void Spambot::loopChannel(std::string msg)
{
	for (std::set<std::string>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		putMsg(_prefix + " PRIVMSG " + *it + " " + msg);
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
		loopChannel(":click to get money");
	else if (rng == 2)
		loopChannel(":your computter require an update");
	else if (rng == 3)
		loopChannel(":turning on your camera");
	else if (rng == 4)
		loopChannel(":you have been hacked");
	else if (rng == 5)
		loopChannel(":your mama");
	else if (rng == 6)
		loopChannel(":how to lose fat easily, doctor hate this");
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
	
	if (cmd.command() == "PRIVMSG")
	{
		if (cmd.argcs(1).find("test"))
			return putMsg(_prefix + " PRIVMSG " + cmd.arg(0) + " j ai trouver ton test ????");
		if (cmd.argcs(1).find("ok"))
			return putMsg(_prefix + " PRIVMSG " + cmd.arg(0) + " kokokokok");
	}
}

void	Spambot::inviteCheck(Cmd cmd)
{
	std::cout << "INVITE " << cmd.arg(1) << std::endl;
	if(cmd.command() == "INVITE")
	{
		if(cmd.arg(0) == _nick)
			putMsg("JOIN " + cmd.arg(1));
		_channels.insert(cmd.arg(1));
	}
}

void	Spambot::botHandle(Cmd cmd)
{
	std::cout << cmd.command() << std::endl;
	if (cmd.command() == "433")
		endBot();
	if (cmd.prefix() == _prefix)
		addCheck(cmd);
	else
	{
		inviteCheck(cmd);
		kickCheck(cmd);
		overReact(cmd);
	}
}

#include <ctime>

void Spambot::vigil()
{
    std::time_t timecheck;
    std::tm*    datetime;
    int         timethen = -1;

    while (_signal)
    {
        timecheck = std::time(NULL);
        datetime = std::localtime(&timecheck);

        receiveData();

        if (_msg.find('\n') != std::string::npos)
        {
            botHandle(_msg);
            _msg.clear();
        }

        if (datetime && datetime->tm_min != timethen)
        {
            timethen = datetime->tm_min;
            spamming();
        }
    }
}

void Spambot::putMsg(const std::string &msg)
{
    std::string output = msg + "\r\n";

    if (send(_socket, output.c_str(), output.size(), 0) == -1)
        endBot();
}

void	Spambot::endBot()
{
	_signal = 0;
}


Spambot::Spambot(int port, std::string nick, std::string pass)
    : _port(port), _socket(-1), _nick(nick),
      _prefix(":" + nick + "!bot@127.0.0.1")
{
	struct sigaction sa;

	sa.sa_handler = Spambot::sa_sig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);

    if (!initSocket())
    {
        endBot();
        return;
    }

    putMsg("PASS " + pass);
    putMsg("NICK " + nick);
    putMsg("USER bot");

    vigil();
}

bool Spambot::initSocket()
{
    sockaddr_in server;

    // Création de la socket
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
		return false;

    // Initialisation de la structure
    std::memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(_port);

    // Adresse du serveur (localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
    {
        close(_socket);
        return false;
    }

    // Connexion
    if (connect(_socket, (sockaddr *)&server, sizeof(server)) == -1)
    {
        close(_socket);
        return false;
    }

    std::cout << "Connect : " << _port << std::endl;
    return true;
}

Spambot::~Spambot()
{
    if (_socket != -1)
	{
		putMsg("QUIT");
        if (close(_socket))
			std::cout << "close soket" << std::endl;
	}
	std::cout << "end bot";
}