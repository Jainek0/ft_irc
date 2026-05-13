
#include "src/header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "nop";
		return 0;
	}

    Server  serv(3232, "truc");

    serv.acceptClient(4242);
    serv.handleCommand(4242, argv[1]);

    std::string str = argv[1];
	return 0;
}