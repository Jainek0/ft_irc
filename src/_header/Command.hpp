
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
		static 	void			fPrivmsg			(Client& user, Cmd& cmd);
		static 	void			fPing			(Client& user, Cmd& cmd);
		static 	void			fQuit			(Client& user, Cmd& cmd);
		static 	void			fInvite			(Client& user, Cmd& cmd);

		static 	void			fUser			(Client& user, Cmd& cmd);
		static 	void			fNick			(Client& user, Cmd& cmd);
		static	void			fPass			(Client& user, Cmd& cmd);





	private:

		static mapCommand_t	createCommands	();

		/*  ------------------< ban >------------------  */

		~Command	();
		Command		();
};

#endif

	/*
	NICK → pseudo
	USER → username/login

	PRIVMSG → message privé / channel
	PING → keepalive
	QUIT → déconnexion

	PASS → mot de passe du serveur
	PART → déconnexion du channel
	INVITE → invite channel

		*/
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
