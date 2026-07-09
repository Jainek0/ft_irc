#include "../header/Spambot.hpp"

int				react = 0;

int	main(int argc, char **argv)
{
	// int			port = atoi(argv[1]);
	// std::string	nick = argv[2];
	// std::string	pass = argv[3];
	Spambot bot(atoi(argv[1]), argv[2], argv[3]);
	int		bit = 0;
	while(bot.signal == 0 && bit == 0)
	{
		receiveData();
	}
	if(bit == 1)
		msg deco
}