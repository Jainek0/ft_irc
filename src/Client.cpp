#include "header/irc.hpp"

//Constructor/destructor
Client::Client(void): 
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
	
}

//getters/setters

//member functions
