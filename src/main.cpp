#include "../header/Spambot.hpp"

int	main(int argc, char **argv)
{
	fdServ;
	int			react;
	time_t		timecheck = time(NULL);
	struct tm	datetime = *localtime(&timecheck);
	int			timethen;
	
	timethen = datetime.tm_min;
	while(1)
	{
		timecheck = time(NULL);
		datetime = *localtime(&timecheck);
		if(react != 0)
		{
			overreact();
		}
		if(datetime.tm_min != timethen)
		{
			timethen = timecheck;
			putmsg(fdServ, "PRIVATEMSG #channel :spamming in progress");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}