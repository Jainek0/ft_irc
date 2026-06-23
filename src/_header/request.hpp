
#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "irc.hpp"

# define SERVER_NAME	std::string("outstanding")
# define SERVER_HOST	std::string("127.0.0.1")


/*  ----------------------- {LOG} -----------------------  */

# define LOG_JOIN_OP(fd, nick, channel)("[" + fd + "] <" + nick + "> join <" + channel + "> as operator")
# define LOG_JOIN_MEMBER(fd, nick, channel)("[" + fd + "] <" + nick + "> join <" + channel + "> as members")
# define LOG_KCIK(fd, nick, kicked, channel)("[" + fd + "] <" + kicked + "> KCIK <" + channel + "> by <" + nick + ">")

# define LOG_TOPIC(fd, nick, channel, topic)("[" + fd + "] <" + nick + "> SET TOPIC [" + channel + "]  <" + topic + ">")


# define LOG_CREATCHANNELPASS(fd, channel, client, pass)("[" + fd + "] channel <" + channel + "> was created by <"  + client + "> with the password <" + pass + ">")
# define LOG_CREATCHANNEL(fd, channel, client)("[" + fd + "] channel <" + channel + "> was created by <"  + client + ">")

# define LOG_START(fd)("[" + fd + "] ------------------------------------------------------------------< start server ")
# define LOG_END(fd)("[" + fd + "] ------------------------------------------------------------------ end server >\n")

# define LOG_ACCEPTCLIENT(fdServ, fdClient)("[" + fdServ + "] <- - - [" + fdClient + "]")


/*  ----------------------- {ERROR} -----------------------  */


# define ERR_UNKNOWNCOMMAND(client, command)(":" + SERVER_NAME + " 421 " + client + " "  + command + " :command is unknown to the server")

# define ERR_UMODEUNKNOWNFLAG(client, flag)(":" + SERVER_NAME + " 501 " + client + " "  + flag + " :Unknown MODE flag")

# define ERR_NOSUCHCHANNEL(client, channel)(":" + SERVER_NAME + " 403 " + client + " " + channel + ":channel name is invalid, or does not exist")

# define ERR_TOOMUCHPARAMS(client, cmd)(client + " " + cmd + " :Too much parameters")
# define ERR_USERONCHANNEL(nick, channel)(":" + SERVER_NAME + " 303 " + nick + " " + channel + " :is already on channel")
# define ERR_NOSUCHNICK(client, nickname)(":" + SERVER_NAME + " 401 " + client + " " + nickname + " :No such nickname")
# define ERR_BADCHANMASK(nick, channel)(":" + SERVER_NAME + " 476 " + nick + " " + channel + " :Bad Channel Mask")
# define ERR_CANNOTSENDTOCHAN(client, channel)(":" + SERVER_NAME + " 404 " + client + " " + channel + " :Cannot send to channel")
# define ERR_NOTEXTTOSEND(client)(":" + SERVER_NAME + " 412 " + client + " :No text to send")

# define ERR_NONICKNAMEGIVEN(client)(":127.0.0.1 431 " + client + " :No nickname given")

# define ERR_ERRONEUSNICKNAME(client, nickname)(":" + SERVER_NAME + " 432 " + client + " " + nickname + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nick)(":" + SERVER_NAME + " 433 " + client + " " + nick + " :Nickname is already in use")
# define ERR_NICKNAMEINUSEC(nick)(":" + SERVER_NAME + " 433 * " + nick + " :Nickname is already in use")
# define ERR_ERRONEUSUSERNAME(client, username)(":" + SERVER_NAME + " 432 " + client + " " + username + " :Erroneus username")
# define ERR_USERNAMEINUSE(client, username)(":127.0.0.1 433 * " + client + " " + username + " :Username is already in use")
# define ERR_NORECIPIENT(client, command)(":" + SERVER_NAME + " 411 " + client + " " + command + " :No recipient given")

# define ERR_USERNOTINCHANNEL(nick, channel)(":" + SERVER_NAME + " 441 " + nick + " " + channel + " :They aren't on that channel")
# define ERR_NOTONCHANNEL(client, channel)(":" + SERVER_NAME + " 442 " + client + " " + channel + " :Not on that channel")
# define ERR_NOTREGISTERED()(":" + SERVER_NAME + " 451 :You have not registered")
# define ERR_NEEDMOREPARAMS(client, cmd)(":" + SERVER_NAME + " 461 " + client + " " + cmd + " :Not enough parameters")
# define ERR_ALREADYREGISTRED(client)(":" + SERVER_NAME + " 462 " + client + " :You may not reregister")
# define ERR_PASSWDMISMATCH(client)(":" + SERVER_NAME + " 464 " + client + " :Password incorrect")
# define ERR_KEYSET(nick, channel)(":" + SERVER_NAME + " 467 " + nick + " " + channel + " :Channel key already set")
# define ERR_CHANNELISFULL(client, channel)(":" + SERVER_NAME + " 471 " + client + " " + channel + " :Cannot join channel (+l)")
# define ERR_UNKNOWNMODE(client, mode)(":" + SERVER_NAME + " 472 " + client + " " + mode + " :is unknown mode char to me")
# define ERR_INVITEONLYCHAN(client, channel)(":" + SERVER_NAME + " 473 " + client + " " + channel + " :Cannot join channel (+i)")
# define ERR_BADCHANNELKEY(client, channel)(":" + SERVER_NAME + " 475 " + client + " " + channel + " :Cannot join channel (+k)")
# define ERR_NOCHANMODES(channel)(":" + SERVER_NAME + " 477 " + channel + " :Channel doesn't support modes")
# define ERR_CHANOPRIVSNEEDED(client, channel)(":" + SERVER_NAME + " 482 " + client + " " + channel + " :You're not channel operator")


# define RPL_ONLY(client, channel)(":" + SERVER_NAME + " 366 " + client + " " + channel + " :End of /NAMES list")

# define JOIN(name, channel) std::string(":" + name + " JOIN :" + channel)
# define WHO(name, tname, tnick, channel, Op) std::string(":" + SERVER_NAME + " 352 " + name + " " + channel + " " + tname + " ircserv 127.0.0.1 " + tnick + " H" + Op + ":0 realname")
# define ENDWHO(name, channel) std::string(":" + SERVER_NAME + " 315 " + name + " " + channel + " :End of /WHO list.")
# define RPL_JOIN(prefix, channel)(prefix + " JOIN " + channel)
# define RPL_PART(prefix, channel)(prefix + " PART " + channel)
# define RPL_MODE(prefix, channel, mode, name)(prefix + " MODE " + channel + " " + mode + " " + name)
# define RPL_KICK(prefix, channel, target)(prefix + " KICK " + channel + " " + target)
# define RPL_NEWKICK(prefix, channel, target, comment)(prefix + " KICK " + channel + " " + target + " :" + comment)
# define RPL_INVITERCVR(prefix, invitee, channel)(prefix + " INVITE " + invitee + " " + channel)
# define RPL_NICK(newNick)(":" + SERVER_NAME + " NICK " + newNick)
# define RPL_TOPIC(prefix, channel, topic)(prefix + " TOPIC " + channel + " :" + topic)
# define RPL_NOTOPIC(client, channel)(":" + SERVER_NAME + " 331 " + client + " " + channel + " :No topic is set")
# define RPL_SEETOPIC(client, channel, topic)(":" + SERVER_NAME + " 332 " + client + " " + channel + " :" + topic)
# define RPL_NAMEREPLY(nick, channel, nicknames)(":" + SERVER_NAME + " 353 " + nick + " = " + channel + " :" + nicknames)
# define ENDLISTCLIENT(name, channel) std::string(":" + SERVER_NAME + " 366 " + name + " " + channel + " :End of /NAMES list.")

# define RPL_CHANNELMODEIS(nick, channel, modes)(": 324 " + nick + " " + channel + " " + modes)



#endif