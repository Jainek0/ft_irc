#include "../header_bonus/Spambot.hpp"

int				react = 0;

int	main(int argc, char **argv)
{

	if (argc < 4)
	{
		std::cout << "spamBot <PORT> <NICK> <PASS>" << std::endl;
		return 0;
	}
	Spambot bot(atoi(argv[1]), argv[2], argv[3]);
	std::cout << "i'm alive" << std::endl;
	bot.loop();
	return 0;
}