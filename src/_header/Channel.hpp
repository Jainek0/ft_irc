#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"

class Channel
{
	public:
		Channel(const std::string& channel_name, const Client& op , const std::string& pasword);
		Channel(const std::string& channel_name, const Client& op);
		Channel(const Channel& other);
		~Channel();

		const std::string	getName			()								const;
		const std::string 	getTopic		()								const;
		bool				emptyPassword	()								const;
		bool 				checkPassword	(const std::string pass) 		const;

		int					findOperator	(const int fd)					const;
		int					findMember		(const int fd)					const;
		int					findUser		(const int fd)					const;
		int					findInvite		(const int fd)					const;

		std::set<int>		getOperator		()								const;
		std::set<int>		getMember		()								const;
		std::set<int>		getUser			()								const;
		std::set<int>		getInvite		()								const;


		bool				getMode			(const char c) 					const;
		void				setMode			(const char c, size_t nb);

		void				setPassword		(const std::string& password);
		void 				setTopic		(const std::string& topic);

		void				grade			(const bool b, const int fd);
		void				addOperator		(const int fd);
		void				addMember		(const int fd);
		void				addInvite		(const int fd);

		void				rmOperator		(const int fd);
		void				rmMember		(const int fd);
		void				rmUser			(const int fd);
		void				rmInvite		(const int fd);

		void				clearInvite		();


		void				log				()								const; // tmp ? ----------------------------------------------



	private:

		const std::string 	_name;
		std::set<int> 		_members;
		std::set<int>		_operators;
		std::set<int>		_invite;
		std::string 		_topic;
		std::string 		_password;
		bool				_i;
		bool				_t;
		size_t				_l;


	/*  ------------------< ban >------------------*/

		Channel&			operator=		(const Channel& other);

};

#endif