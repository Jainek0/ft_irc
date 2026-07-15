#include "src/_header/irc.hpp"

int g_sig = 0;

int	init(Server &myserver)//, struct sigaction &signal)
{
	try
	{
		myserver.setup();
		std::cout << "Server listening on port " << myserver.getPort() << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	//is it necessary to while(isdigit) input?
	if (argc != 3 || !(atoi(argv[1]) > 1023 && atoi(argv[1]) < 65535))
	{
		std::cout << "please format input as :" << std::endl;
		std::cout << "./ircserv Port<int>(1024-65535) Password<string>" << std::endl;
		return 0;
	}
	
	int port = atoi(argv[1]);
	Server &myserver = Server::getInstance(port, argv[2]);
	// struct sigaction	signal;
	// memset(&signal, 0, sizeof(signal));
	if (init(myserver))
		return (1);

	//main loop
	while(!g_sig)
	{
		int	retpoll = poll(myserver.getPollfds(), 1024, 1000);
		if (retpoll == -1 && !g_sig)
		{
			std::cerr << "poll error" << std::endl;
			return(1);
		}
		if (retpoll == 0)
			continue ;
		for(int i = 0; i < 1024; i++)
		{
			if ((myserver.getPollfds(i)).revents == POLLIN)//&POLLIN?
			{
				if ((myserver.getPollfds(i)).fd == myserver.getServFd())
					myserver.acceptClient();
				else
					myserver.recieveData((myserver.getPollfds(i)).fd);
			}
		}
	}
	return 0;
}
