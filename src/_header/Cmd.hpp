
#ifndef CMD_HPP
# define CMD_HPP

# include "irc.hpp"

class Cmd
{
    public:
        Cmd(std::string& str);
        Cmd(const Cmd& other);
        Cmd& operator=(const Cmd& other);
        ~Cmd();

        const	std::string& 				prefix		() 			const;
        const	std::string& 				command		() 			const;
        const	std::string& 				arg			(size_t i)	const;
        const	std::string 				argcs		(size_t i)	const;
        const	std::vector<std::string> & 	args		()			const;
        		size_t 						sizeArgs	()			const;

    private:
        std::string                 		_prefix;
        std::string                 		_command;
        std::vector<std::string>    		_args;
};

#endif