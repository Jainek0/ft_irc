
#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "irc.hpp"

# define SERVER_NAME std::string("outstanding")


/*  ----------------------- {LOG} -----------------------  */

# define LOG_JOIN(fd, client, cmd)("[" + fd + "] <" + client + "> join <" + cmd + ">")

# define LOG_CREATCHANNELPASS(fd, channel, client, pass)("[" + fd + "] channel <" + channel + "> was created by <"  + client + "> with the password <" + pass + ">")
# define LOG_CREATCHANNEL(fd, channel, client)("[" + fd + "] channel <" + channel + "> was created by <"  + client + ">")

# define LOG_START(fd)("[" + fd + "] ------------------------------------------------------------------< start server ")
# define LOG_END(fd)("[" + fd + "] ------------------------------------------------------------------ end server >\n")

# define LOG_ACCEPTCLIENT(fdServ, fdClient)("[" + fdServ + "] <- - - [" + fdClient + "]")


/*  ----------------------- {ERROR} -----------------------  */


# define ERR_UNKNOWNCOMMAND(command)(":" + SERVER_NAME + " 421 " + command + " :command is unknown to the server\r\n")


# define ERR_TOOMUCHPARAMS(client, cmd)(client + " " + cmd + " :Too much parameters\r\n")
# define ERR_USERONCHANNEL(nick, channel)(":" + SERVER_NAME + " 303 " + nick + " " + channel + " :is already on channel\r\n")
# define ERR_NOSUCHNICK(client, nickname)(":" + SERVER_NAME + " 401 " + client + " " + nickname + " :No such nickname\r\n")
# define ERR_BADCHANMASK(nick, channel)(":server 476 " + nick + " " + channel + " :Bad Channel Mask")
# define ERR_CANNOTSENDTOCHAN(client, channel)(":" + SERVER_NAME + " 404 " + client + " " + channel + " :Cannot send to channel\r\n")
# define ERR_NOTEXTTOSEND(client)(":" + SERVER_NAME + " 412 " + client + " :No text to send\r\n")

# define ERR_NONICKNAMEGIVEN(client)(":127.0.0.1 431 " + client + " :No nickname given\r\n")

# define ERR_ERRONEUSNICKNAME(client, nickname)(":" + SERVER_NAME + " 432 " + client + " " + nickname + " :Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nick)(":127.0.0.1 433 " + client + " " + nick + " :Nickname is already in use\r\n")
# define ERR_NICKNAMEINUSEC(nick)(":127.0.0.1 433 * " + nick + " :Nickname is already in use\r\n")
# define ERR_ERRONEUSUSERNAME(client, username)(":" + SERVER_NAME + " 432 " + client + " " + username + " :Erroneus username\r\n")
# define ERR_USERNAMEINUSE(client, username)(":127.0.0.1 433 * " + client + " " + username + " :Username is already in use\r\n")
# define ERR_NORECIPIENT(client, command)(":" + SERVER_NAME + " 411 " + client + " " + command + " :No recipient given\r\n")

# define ERR_USERNOTINCHANNEL(client, nick, channel)(":" + SERVER_NAME + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")
# define ERR_NOTONCHANNEL(client, channel)(":" + SERVER_NAME + " 442 " + client + " " + channel + " :Not on that channel\r\n")
# define ERR_NOTREGISTERED()(":" + SERVER_NAME + " 451 :You have not registered\r\n")
# define ERR_NEEDMOREPARAMS(client, cmd)(":" + SERVER_NAME + " 461 " + client + " " + cmd + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTRED(client)(":127.0.0.1 462 " + client + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(client)(":127.0.0.1 464 " + client + " :Password incorrect\r\n")
# define ERR_KEYSET(nick, channel)(":127.0.0.1 467 " + nick + " " + channel + " :Channel key already set\r\n")
# define ERR_CHANNELISFULL(client, channel)(":" + SERVER_NAME + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
# define ERR_UNKNOWNMODE(client, mode)(":" + SERVER_NAME + " 472 " + client + " " + mode + " :is unknown mode char to me\r\n")
# define ERR_INVITEONLYCHAN(client, channel)(":" + SERVER_NAME + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
# define ERR_BADCHANNELKEY(client, channel)(":" + SERVER_NAME + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
# define ERR_NOCHANMODES(channel)(":" + SERVER_NAME + " 477 " + channel + " :Channel doesn't support modes\r\n")
# define ERR_CHANOPRIVSNEEDED(client, channel)(":" + SERVER_NAME + " 482 " + client + " " + channel + " :You're not channel operator\r\n")

#endif