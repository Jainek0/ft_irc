*This project has been created as part of the 42 curriculum by thcaquet, ledupont, agamay.*

# ft_irc

# Description

**ft_irc** is a simplified implementation of an Internet Relay Chat (IRC) server written in **C++98**.

The objective of this project is to understand how IRC servers work by implementing the IRC protocol and handling multiple simultaneous clients using non-blocking I/O. The server must be compatible with a standard IRC client such as HexChat.

The server supports authenticated users, channel management, private messaging, operator privileges, and the basic IRC commands required by the project subject.

This project focuses on:

- Network programming using TCP sockets.
- Event-driven programming with `poll()`.
- Client connection management.
- Parsing and processing IRC commands.
- Channel and user management.
- Writing clean and modular C++98 code.

# Instructions

Compile the IRC server and execute it providing a connection port and a password. 
ex: "./ircserv 4545 pass"

Once the server is running, you can connect a client using either hexchat, or the command "nc -C localhost <port>" from another terminal.

In order to authenticate, you will need a nickname, username and to enter the password.
You can use the commands NICK <nickname>, USER <username>, PASS <password> in a connected terminal.
Or they can be configured in Hexchat thanks to the "edit" window.
Note that a Hexchat not configured properly with the right password won't be able to authenticate after connection.

# Features

Once the server is running and has authenticated clients connected, you can use a variety of commands:

Any user commands :
- NICK <nickname>
- PASS <password>
- USER <username>
- JOIN #<channel_name>
- PART <channel>
- PRIVMSG <username> <message>
- TOPIC
- INVITE <username> <channel_name>

Operator only commands :
- KICK <username> <channel_name>
- MODE

Note : hexchat syntax ;"/<COMMAND>"

# Resources

Official documentation:
- for poll, sockets and other functions : https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf
- for commands : https://www.rfc-editor.org/rfc/rfc1459.html
- IRC norm : https://www.alien.net.au/irc/irc2numerics.html

# AI Usage

Artificial Intelligence was used for the Tools code and this README.md description.
