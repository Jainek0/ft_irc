

#include "../header/irc.hpp"

Channel::Channel()
{}

Channel::Channel(std::string channel_name, std::string op ,std::string pasword)
    : _channel_name(channel_name), _pasword(pasword)
{
    std::cout << "channel <" << this->_channel_name << "> was created by <"  << op << "> with the password <" << pasword << ">" << std::endl;
    _operators.insert(op);
}

Channel::Channel(std::string channel_name, std::string op)
    : _channel_name(channel_name)
{
    std::cout << "channel <" << this->_channel_name << "> was created by <"  << op << ">" << std::endl;
    _operators.insert(op);
}

Channel::Channel(const Channel& other)
{
    *this = other;
}

Channel& Channel::operator=(const Channel& other)
{
    if (this != &other)
    {
        this->_channel_name = other._channel_name;
        this->_pasword = other._pasword;
        this->_operators = other._operators;
        this->_members = other._members;
        this->_i = other._i;
        this->_l = other._l;
        this->_t = other._t;
    }
    return *this;
}

Channel::~Channel()
{
    // if (!this->_channel_name.empty())
    //     std::cout << "channel <" << this->_channel_name << "> is destroy" << std::endl;
}



