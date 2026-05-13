#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "irc.hpp"

class Channel
{
	public:
		Channel(const std::string& channel_name, const Client& op , const std::string& pasword);
		Channel(const std::string& channel_name, const Client& op);
		Channel(const Channel& other);
		~Channel();

		bool				emptyPassword()							const;
		const std::string 	getPassword()							const;
		const std::string 	getTopic()								const;
		const std::string	channelName()							const;

		int					findOperator(const std::string& nick)	const;
		int					findMember(const std::string& nick)		const;
		int					findOperator(const int pid)				const;
		int					findMember(const int pid)				const;

		void				setPassword(const std::string& password);
		void 				setTopic(const std::string& topic);

		void				addOperator(const int pid);
		void				addMember(const int pid);

		void				rmOperator(const int pid);
		void				rmMember(const int pid);
	
	private:

		const std::string 		_channelName;
		std::set<int> 			_members;
		std::set<int> 			_operators;
		std::string 			_topic;
		std::string 			_pasword;
		bool					_i;
		bool					_t;
		size_t					_l;


	/*  ------------------< ban >------------------*/

		Channel& operator=(const Channel& other);

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