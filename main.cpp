#include "src/header/irc.hpp"

int	init(Server myserver, int port, char *password)
{
	try
	{
		myserver.setup(port, password);
		std::cout << "Server listening on port " << _port << std::endl;
	}
	catch(std::exception &e)
	{
		//clear
		std::cout << e.what() << std::endl;
		return (-1);
	}
	//setup signal
	
	return (0)
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
	Server	myserver(port, argv[2]);
	if (init(myserver))
		return (1);
	//main loop
	while(1)//while sigal == false
	{
		int retpoll = (poll(&(myserver._myfds), myserver._myfds.size(), -1))
		if (retpoll == -1)
		{
			std::cout << "poll error" << std::endl;
			//close all fds
			exit(1);
		}
		for(int i = 0; i < 1023; i++)
		{
			if (myserver._myfds[i].revents == POLLIN)//&POLLIN?
			{
				if (myserver._myfds[i].fd == myserver._servfd)
					myserver.acceptClient();
				else
					myserver.recieveData(fds[i].fd);
			}
		}
	}
	return 0;
}
