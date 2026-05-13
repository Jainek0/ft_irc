#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <iomanip>
#include <fstream>
#include <ctime>


/*  ----------------------- {SRC} -----------------------  */

#include "Cmd.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

#include "request.hpp"

#include "../tools/toString.hpp"

/*  ----------------------- {define} -----------------------  */

#define ERR_BAD_PID "ERROR : BAD DEFINE PID"


/*  ----------------------- {func} -----------------------  */


/*  ------------------< tools  */

std::vector<std::string> split(const std::string& str, char sep);
void logScript(const std::string& str);

/*  ------------------< commands  */

std::map<std::string, void(*)(Client&, Cmd&)> createCommands();


#endif