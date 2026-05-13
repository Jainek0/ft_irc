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

		int					findOperator(const int pid)				const;
		int					findMember(const int pid)				const;

		bool				getMode(const char c) 					const;
		void				setMode(const char c, size_t nb);

		void				setPassword(const std::string& password);
		void 				setTopic(const std::string& topic);

		void				addOperator(const int pid);
		void				addMember(const int pid);

		void				rmOperator(const int pid);
		void				rmMember(const int pid);



	
	private:

		const std::string 			_channelName;
		std::set<int> 	_members;
		std::set<int> 	_operators;
		std::string 				_topic;
		std::string 				_pasword;
		bool						_i;
		bool						_t;
		size_t						_l;


	/*  ------------------< ban >------------------*/

		Channel& operator=(const Channel& other);

};

#endif