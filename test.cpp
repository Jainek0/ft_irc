
#include "src/header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "nop";
		return 0;
	}

    Server  serv(3232, "truc");

	int pid(4242);
    serv.acceptClient(pid);
	if (serv.checkClient(pid))
   		serv.handleCommand(serv.findClient(pid), argv[1]);

    std::string str = argv[1];
	return 0;
}