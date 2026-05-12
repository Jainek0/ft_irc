
#include "src/header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "nop";
		return 0;
	}

    Client  me(4242);
    Channel cha("regarde comme je suis beau", me._fd);

    std::string str = argv[1];
    Cmd cmd(str);

	return 0;
}