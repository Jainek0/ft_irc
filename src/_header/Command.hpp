#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "../_header/irc.hpp"

class Command
{
	public:

		static void	 		handleCommand	(Client& user, std::string str);

		/*  ------------------< commands >------------------  */

		static 	void			fJoin		(Client& user, Cmd& cmd);
		static 	void			fKick			(Client& user, Cmd& cmd);
		static 	void			fMode			(Client& user, Cmd& cmd);
		static 	void			fTopic			(Client& user, Cmd& cmd);
		static 	void			fPrivmsg		(Client& user, Cmd& cmd);
		static 	void			fQuit			(Client& user, Cmd& cmd);
		static 	void			fInvite			(Client& user, Cmd& cmd);

		static 	void			fUser			(Client& user, Cmd& cmd);
		static 	void			fNick			(Client& user, Cmd& cmd);
		static	void			fPass			(Client& user, Cmd& cmd);

		void					nickname		(Client &user);
		void					username		(Client &user);
		void					password		(Client &user);

	private:
		static mapCommand_t	createCommands	();
		/*  ------------------< ban >------------------  */
		~Command	();
		Command		();
};

#endif

