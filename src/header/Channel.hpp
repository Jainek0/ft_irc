#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "irc.hpp"

class Channel
{
	public:
		Channel(std::string channel_name, std::string pasword);
		Channel(std::string channel_name);
		Channel(Channel& other);
		Channel& operator=(Channel& other);
		~Channel();

	private:
		std::set<int> 	_members;
		std::set<int> 	_operators;
		std::string 	_channel_name;
		std::string 	_pasword;
		bool			_i;
		bool			_t;
		int				_l;

	// void bultin_[...](std::string str);

	// [
	// 	∗ KICK - Eject a client from the channel
	// 	∗ INVITE - Invite a client to a channel
	// 	∗ TOPIC - Change or view the channel topic
	// 	∗ MODE - Change the channel’s mode:
	// 		· i: Set/remove Invite-only channel
	// 		· t: Set/remove the restrictions of the TOPIC command to channel
	// 		operators
	// 		· k: Set/remove the channel key (password)
	// 		· o: Give/take channel operator privilege
	// 		· l: Set/remove the user limit to channel
	// ]
};


#endif