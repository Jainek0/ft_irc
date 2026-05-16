#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <set>
# include <map>

# include <iomanip>
# include <fstream>
# include <ctime>



/*  ----------------------- {FORWARD DECL} -----------------------  */

class Client;
class Cmd;
class Channel;

/*  ----------------------- {typedef} -----------------------  */

typedef void (*command_t)(Client&, Cmd&);
typedef std::map<std::string, command_t> mapCommand_t;

typedef std::map<std::string, Channel> mapChannel_t;
typedef mapChannel_t it_mapChannel_t;

typedef std::map<int, Client> mapClient_i_t;
typedef std::map<std::string, Client> mapClient_s_t;



/*  ----------------------- {SRC} -----------------------  */

# include "Cmd.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Command.hpp"

# include "request.hpp"

# include "../tools/toString.hpp"

/*  ----------------------- {define} -----------------------  */


# define ERR_BAD_PID "ERROR : BAD DEFINE PID"


/*  ----------------------- {func} -----------------------  */



/*  ------------------< tools  */

std::vector<std::string> split(const std::string& str, char sep);
void logScript(const std::string& str);

/*  ------------------< commands  */

#endif