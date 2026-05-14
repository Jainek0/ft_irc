

#include "../_header/irc.hpp"

Channel::Channel(const std::string& channel_name, const Client& op , const std::string& password)
    : _channelName(channel_name), _password(password), _i(0), _t(0), _l(0)
{
    logScript(LOG_CREATCHANNELPASS(toString(op.fd()), this->_channelName, op.getNick(), password));
    _operators.insert(op.fd());
}

Channel::Channel(const std::string& channel_name, const Client& op)
    : _channelName(channel_name), _i(0), _t(0), _l(0)
{
    logScript(LOG_CREATCHANNEL(toString(op.fd()), this->_channelName, op.getNick()));
    _operators.insert(op.fd());
}

Channel::Channel(const Channel& other)
    : _channelName(other._channelName), _password(other._password), _i(0), _t(0), _l(0)
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



bool Channel::emptyPassword() const { return _password.empty(); }


bool Channel::checkPassword(std::string pass) const { return _password == pass; }

const std::string Channel::getTopic() const { return _topic; }

void Channel::setPassword(const std::string& password) { _password = password; }

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

