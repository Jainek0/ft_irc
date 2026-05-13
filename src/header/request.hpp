
#ifndef REQUEST_HPP
#define REQUEST_HPP


/*  ----------------------- {LOG} -----------------------  */

#define LOG_JOIN(client, cmd)("<" + client + "> join <" + cmd + ">")

#define LOG_CREATCHANNELPASS(channel, client, pass)("channel <" + channel + "> was created by <"  + client + "> with the password <" + pass + ">")
#define LOG_CREATCHANNEL(channel, client)("channel <" + channel + "> was created by <"  + client + ">")

#define LOG_START(fd)("[" + fd + "] ------------------------------------------------------------------< start server ")
#define LOG_END(fd)("[" + fd + "] ------------------------------------------------------------------ end server >\n")

#define LOG_ACCEPTCLIENT(fd, nick, username)("[" + fd + "] new client connected ->  <" + nick + "> <" + username + ">")


/*  ----------------------- {ERROR} -----------------------  */


#define ERR_TOOMUCHPARAMS(client, cmd)(client + " " + cmd + " :Too much parameters\r\n")
#define ERR_USERONCHANNEL(nick, channel)(": 303 " + nick + " " + channel + " :is already on channel\r\n")
#define ERR_NOSUCHNICK(client, nickname)(": 401 " + client + " " + nickname + " :No such nickname\r\n")
#define ERR_BADCHANMASK(nick, channel)(":server 476 " + nick + " " + channel + " :Bad Channel Mask")
#define ERR_CANNOTSENDTOCHAN(client, channel)(": 404 " + client + " " + channel + " :Cannot send to channel\r\n")
#define ERR_NOTEXTTOSEND(client)(": 412 " + client + " :No text to send\r\n")

#define ERR_NONICKNAMEGIVEN(client)(":127.0.0.1 431 " + client + " :No nickname given\r\n")

#define ERR_ERRONEUSNICKNAME(client, nickname)(": 432 " + client + " " + nickname + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(client, nick)(":127.0.0.1 433 " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_NICKNAMEINUSEC(nick)(":127.0.0.1 433 * " + nick + " :Nickname is already in use\r\n")
#define ERR_ERRONEUSUSERNAME(client, username)(": 432 " + client + " " + username + " :Erroneus username\r\n")
#define ERR_USERNAMEINUSE(client, username)(":127.0.0.1 433 * " + client + " " + username + " :Username is already in use\r\n")
#define ERR_NORECIPIENT(client, command)(": 411 " + client + " " + command + " :No recipient given\r\n")

#define ERR_USERNOTINCHANNEL(client, nick, channel)(": 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(client, channel)(": 442 " + client + " " + channel + " :Not on that channel\r\n")
#define ERR_NOTREGISTERED()(": 451 :You have not registered\r\n")
#define ERR_NEEDMOREPARAMS(client, cmd)(": 461 " + client + " " + cmd + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED(client)(":127.0.0.1 462 " + client + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(client)(":127.0.0.1 464 " + client + " :Password incorrect\r\n")
#define ERR_KEYSET(nick, channel)(":127.0.0.1 467 " + nick + " " + channel + " :Channel key already set\r\n")
#define ERR_CHANNELISFULL(client, channel)(": 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_UNKNOWNMODE(client, mode)(": 472 " + client + " " + mode + " :is unknown mode char to me\r\n")
#define ERR_INVITEONLYCHAN(client, channel)(": 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(client, channel)(": 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_NOCHANMODES(channel)(": 477 " + channel + " :Channel doesn't support modes\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel)(": 482 " + client + " " + channel + " :You're not channel operator\r\n")

#endif