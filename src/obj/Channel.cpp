

#include "../header/irc.hpp"

Channel::Channel(const std::string& channel_name, const Client& op , const std::string& password)
    : _channelName(channel_name), _pasword(password), _i(0), _t(0), _l(0)
{
    logScript(LOG_CREATCHANNELPASS(this->_channelName, op.nick(), password));
    _operators.insert(op.fd());
}

Channel::Channel(const std::string& channel_name, const Client& op)
    : _channelName(channel_name), _i(0), _t(0), _l(0)
{
    logScript(LOG_CREATCHANNEL(this->_channelName, op.nick()));
    _operators.insert(op.fd());
}

Channel::Channel(const Channel& other)
    : _channelName(other._channelName), _pasword(other._pasword), _i(0), _t(0), _l(0)
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
{}

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


bool Channel::getMode(const char c) const
{
    if (c == 'l')
    {
        if (!_l)
            return 0;
        return (_members.size() + _operators.size() >= _l);
    }
    else if (c == 'i')
        return _i;
    return _t;
}

void Channel::setMode(const char c, size_t nb)
{
    if (c == 'l')
        _l = nb;
    else if (c == 'i')
        _i = (nb > 0);
    else if (c == 't')
        _t = (nb > 0);
}

