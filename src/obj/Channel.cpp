

#include "../header/irc.hpp"

Channel::Channel(const std::string& channel_name, const Client& op , const std::string& pasword)
    : _channelName(channel_name), _pasword(pasword)
{
    std::cout << "channel <" << this->_channelName << "> was created by <"  << op.nick() << "> with the password <" << pasword << ">" << std::endl;
    _operators.insert(op.fd());
}

Channel::Channel(const std::string& channel_name, const Client& op)
    : _channelName(channel_name)
{
    std::cout << "channel <" << this->_channelName << "> was created by <"  << op.nick() << ">" << std::endl;
    _operators.insert(op.fd());
}

Channel::Channel(const Channel& other)
    : _channelName(other._channelName), _pasword(other._pasword)
{}

// Channel& Channel::operator=(const Channel& other)
// {
//     if (this != &other)
//     {
//         this->_pasword = other._pasword;
//         this->_operators = other._operators;
//         this->_members = other._members;
//         this->_i = other._i;
//         this->_l = other._l;
//         this->_t = other._t;
//     }
//     return *this;
// }

Channel::~Channel()
{
    // if (!this->_channel_name.empty())
    //     std::cout << "channel <" << this->_channel_name << "> is destroy" << std::endl;
}

int Channel::findOperator(const std::string& nick) const 
{
    // Implementation needed - search operator by nickname
    (void) nick;
    return -1;
}

int Channel::findMember(const std::string& nick) const 
{
    // Implementation needed - search member by nickname
    (void) nick;
    return -1;
}

int Channel::findOperator(int pid) const
{
    if (_operators.find(pid) != _operators.end())
        return pid;
    return -1;
}

int Channel::findMember(int pid) const
{
    if (_members.find(pid) != _members.end())
        return pid;
    return -1;
}



bool Channel::emptyPassword() const { return _pasword.empty(); }

const std::string Channel::getPassword() const { return _pasword; }

const std::string Channel::getTopic() const { return _topic; }

void Channel::setPassword(const std::string& password) { _pasword = password; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

void Channel::addOperator(int pid) { _operators.insert(pid); }

void Channel::addMember(int pid) { _members.insert(pid); }

void Channel::rmOperator(int pid) { _operators.erase(pid); }

void Channel::rmMember(int pid) { _members.erase(pid); }

const std::string Channel::channelName() const { return _channelName; }