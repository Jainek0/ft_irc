#include "../header/Spambot.hpp"

void joinChannel(std::string channel)
{
	putmsg(fdServ, "JOIN #channel");
	putmsg(fdServ, "PRIVATEMSG #channel :coucou les amis, il faut que je vous parle de ma nouvelle crypto");
}

void overreact(std::string msg)
{
	std::map<std::string, std::string> shout;
	shout.insert("pile", "macron explosion face");
	shout.insert("face", "macron decapitation pile");
	std::ostringstream os(msg);
	for (std::string str << os; str; str << os)
	{
		box::iterator it shout.find(str);
		if (it != shout.end()) {
			putmsg(it->second);

		}
	}
}
