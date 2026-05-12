

#include "../header/irc.hpp"

Channel::Channel(std::string channel_name, int op ,std::string pasword)
    : _channel_name(channel_name), _pasword(pasword)
{
    std::cout << "chanell " << this->_channel_name << "is creat" << std::endl;
    _operators.insert(op);
}

Channel::Channel(std::string channel_name, int op)
    : _channel_name(channel_name)
{
    std::cout << "chanell " << this->_channel_name << "is creat" << std::endl;
    _operators.insert(op);
}

Channel::Channel(Channel& other)
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
    std::cout << "chanell " << this->_channel_name << "is destroy" << std::endl;
}




