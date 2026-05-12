
#include "src/header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "nop";
		return 0;
	}

    Client  me(4242);
    Channel cha("regarde comme je suis beau", me);
    cha.
	return 0;
}