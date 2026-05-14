
#include "src/_header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "nop";
		return 0;
	}

    Server&  serv = Server::getInstance(3232, "pass");

	int pid(4242);
    serv.acceptClient();
	argv++;
	while (*argv)
	{
		if (serv.checkClient(pid))
			   Command::handleCommand((serv.findClient(pid))->second, *argv++);
	}
	

    std::string str = argv[1];
	return 0;
}