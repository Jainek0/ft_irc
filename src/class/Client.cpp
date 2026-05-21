#include "../_header/irc.hpp"

//Constructor/destructor
Client::Client(int fd): _fd(fd)
{
	std::cout << "Client obj created" << std::endl;
}

Client::Client(Client &og)
{
	*this = og;
	std::cout << "Client obj copied" << std::endl;
}

Client::~Client(void)
{
	std::cout << "Client deleted" << std::endl;
}

//overload operators
Client	&Client::operator=(Client &og)
{
	(void)og;
	return(*this);
}

//getters/setters

//member functions
