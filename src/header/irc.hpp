#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>


/*  ----------------------- {SRC} -----------------------  */

#include "Cmd.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

/*  ----------------------- {define} -----------------------  */

#define ERR_BAD_PID "ERROR : BAD DEFINE PID"


/*  ----------------------- {func} -----------------------  */


/*  ------------------< tools  */

std::vector<std::string> split(const std::string& str, char sep);

/*  ------------------< commands  */

std::map<std::string, void(*)(Client&, Cmd&)> createCommands();


#endif