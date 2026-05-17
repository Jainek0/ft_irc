

#include "../_header/irc.hpp"

Channel::Channel(const std::string& channel_name, const Client& op , const std::string& password)
    : _name(channel_name), _password(password), _i(0), _t(0), _l(0)
{
    logScript(LOG_CREATCHANNELPASS(toString(op.getFd()), this->_name, op.getNickName(), password));
    _operators.insert(op.getFd());
}

Channel::Channel(const std::string& channel_name, const Client& op)
    : _name(channel_name), _i(0), _t(0), _l(0)
{
    logScript(LOG_CREATCHANNEL(toString(op.getFd()), this->_name, op.getNickName()));
    _operators.insert(op.getFd());
}

Channel::Channel(const Channel& other)
    : _name(other._name), _password(other._password), _i(0), _t(0), _l(0)
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

int Channel::findOperator(int fd) const
{
    if (_operators.find(fd) != _operators.end())
        return fd;
    return -1;
}

int Channel::findMember(int fd) const
{
    if (_members.find(fd) != _members.end())
        return fd;
    return -1;
}

int Channel::findUser(int fd) const
{
    if (_members.find(fd) != _members.end())
        return fd;
    if (_operators.find(fd) != _operators.end())
        return fd;
    return -1;
}



bool Channel::emptyPassword() const { return _password.empty(); }


bool Channel::checkPassword(std::string pass) const { return _password == pass; }

const std::string Channel::getTopic() const { return _topic; }

void Channel::setPassword(const std::string& password) { _password = password; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

void Channel::grade(bool b, int fd)
{ 
    if (b)
    {
        _members.erase(fd);
        _operators.insert(fd);
    }
	else
	{
		_operators.erase(fd);
        _members.insert(fd);
	}
}

void Channel::addOperator(int fd)
{ 
	if (findUser(fd) <= 0)
		_operators.insert(fd); 
}

void Channel::addMember(int fd)
{ 
	if (findUser(fd) <= 0)
		_members.insert(fd); 
}

void Channel::rmOperator(int fd) { _operators.erase(fd); }

void Channel::rmMember(int fd) { _members.erase(fd); }

void Channel::rmUser(int fd)
{
    if (_operators.find(fd) != _operators.end())
        _operators.erase(fd); 
    else
        _members.erase(fd); 
}


std::set<int>	Channel::getOperator()	const {return _operators;}

std::set<int>	Channel::getMember()	const {return _members;}

std::set<int>	Channel::getUser()	const 
{
    std::set<int> tmp(_members);
    for (std::set<int>::iterator it = _operators.begin(); it != _operators.end(); ++it)
        tmp.insert(*it);
    return tmp;
}

const std::string Channel::getName() const { return _name; }

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


void Channel::log() const
{
    std::string str( "[" + _name + "] operators <");
    for (std::set<int>::iterator it = _operators.begin(); it != _operators.end(); )
    {
        str += toString(*it);
        if ((++it) != _operators.end())
            str += ",";
    }

    str += "> members <";
    for (std::set<int>::iterator it = _members.begin(); it != _members.end(); )
    {
        str += toString(*it);
        if ((++it) != _members.end())
            str += ",";
    }
    str += "> mode \t:";

	str += "\n\t\t\t\t\t password: <" + _password + ">";
	str += "\n\t\t\t\t\t topic: <" + _topic + ">";
	str += "\n\t\t\t\t\t t: <" + toString(_t) + ">";
	str += "\n\t\t\t\t\t l: <" + toString(_l) + ">";
	str += "\n\t\t\t\t\t i: <" + toString(_i) + ">";

    logScript(str);
}