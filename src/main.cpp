#include "_header/irc.hpp"

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
	if (argc != 3 || !(atoi(argv[1]) > 1023 && atoi(argv[1]) < 65535))
	{
		std::cout << "please format input as :" << std::endl;
		std::cout << "./ircserv Port<int>(1024-65535) Password<string>" << std::endl;
		return 0;
	}
	
	int port = atoi(argv[1]);
	Server &myserver = Server::getInstance(port, argv[2]);
	if (init(myserver))
		return 1;
		
	if (myserver.loop())
		return 1;
	return 0;
}
