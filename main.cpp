
#include "src/header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "true exec : ./ircserv PID PASSWORD";
		return 0;
	}
	size_t pid = atoi(argv[1]);
	while (*argv[1])
	{
		if (!isdigit(*argv[1]))
		{
			std::cerr << ERR_BAD_PID << std::endl;
			return 0;
		}
	}
	
	return 0;
}
