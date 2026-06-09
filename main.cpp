#include "src/_header/irc.hpp"

int	init(Server &myserver)//, struct sigaction &signal)
{
	try
	{
		myserver.setup();
		std::cout << "Server listening on port " << myserver.getPort() << std::endl;
	}
	catch(std::exception &e)
	{
		//clear
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	//setup signal
	
	return (0);
}

int	main(int argc, char **argv)
{
	//is it necessary to while(isdigit) input?
	int port = atoi(argv[1]);
	if (argc != 3 || !(port > 1023 && port < 65535))
	{
		std::cout << "please format input as :" << std::endl;
		std::cout << "./ircserv Port<int>(1024-65535) Password<string>" << std::endl;
		return 0;
	}

	Server &myserver = Server::getInstance(port, argv[2]);
	// struct sigaction	signal;
	// memset(&signal, 0, sizeof(signal));
	if (init(myserver))//, signal
		return (1);
	//main loop
	while(1)//while sigal == false
	{
		if (poll(myserver.getPollfds(), 1024, -1) == -1)
		{
			std::cout << "poll error" << std::endl;
			//close all fds
			return(1);
		}
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
