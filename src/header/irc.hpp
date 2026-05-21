#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <string>
# include <set>
# include <map>
# include <sys/socket.h>//socket, bind, ...
# include <arpa/inet.h>//inet_pton, htons, ...
# include <cstdio>//perror
# include <cerrno>//errno
# include <cstdlib>//exit
# include <unistd.h>//close
# include <poll.h>//poll
# include <csignal>//signal

/*  ------------------- {SRC} -------------------  */

# include "Channel.hpp"
# include "Server.hpp"
# include "Client.hpp"

/*  ------------------- {define} -------------------  */

# define ERR_BAD_PID "ERROR : BAD DEFINE PID"


/*  ------------------- {func} -------------------  */



#endif