#include "../header/Spambot.hpp"

int				react = 0;

int	main(int argc, char **argv)
{

	if (argc < 4)
	{
		std::cout << "sapmBot <PORT> <NICK> <PASS>" << std::endl;
		return 0;
	}
	Spambot bot(atoi(argv[1]), argv[2], argv[3]);
	std::cout << "test" << std::endl;
	while (bot.getSignal())
	{
		std::cout << "while" << std::endl;
		bot.receiveData();
	}
	return 0;
}