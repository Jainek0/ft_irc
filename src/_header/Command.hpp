
#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "../_header/irc.hpp"

class Command
{
	public:

		static void	 		handleCommand	(Client& user, std::string str);

		/*  ------------------< commands >------------------  */

		static void			join			(Client& user, Cmd& cmd);
		static void			kick			(Client& user, Cmd& cmd);
		static void			mode			(Client& user, Cmd& cmd);
		static void			topic			(Client& user, Cmd& cmd);
		static void			privmsg			(Client& user, Cmd& cmd);
		static void			ping			(Client& user, Cmd& cmd);
		static void			quit			(Client& user, Cmd& cmd);
		static void			invite			(Client& user, Cmd& cmd);





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
