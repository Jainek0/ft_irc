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


Channel::~Channel()
{}

bool Channel::checkOperator()
{
    if (_operators.size() == 0 && _members.size() == 0)
        return 1;
    else if (_operators.size() == 0 && _members.size() > 0)
    {
        _operators.insert(*_members.begin());
        _members.erase(*_members.begin());
        Server& serv = Server::getInstance();
        Client target = serv.findClient(*_operators.begin())->second;
        serv.putMsg(*this, RPL_MODE_P(SERVER_PREFIX, _name, "o", target.getNickName()));
    }
    return 0;
}

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

int Channel::findInvite(int fd) const
{
    if (_invite.find(fd) != _invite.end())
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
	if (findUser(fd) == -1)
	{
		rmInvite(fd);
		_operators.insert(fd);

		Server& serv = Server::getInstance();
		serv.findClient(fd)->second.addChannel(_name);
	}
}

void Channel::addMember(int fd)
{ 
	if (findUser(fd) == -1)
	{
		rmInvite(fd);
		_members.insert(fd);

		Server& serv = Server::getInstance();
		serv.findClient(fd)->second.addChannel(_name);
	}
}

void Channel::addInvite(int fd)
{ 
	_invite.insert(fd); 
}

void Channel::rmOperator(int fd) { 
	_operators.erase(fd);
}

void Channel::rmMember(int fd) {
	_members.erase(fd); 
}

void Channel::rmInvite(int fd) { 
	_invite.erase(fd);
}

void Channel::rmUser(int fd)
{
    if (_operators.find(fd) != _operators.end())
        _operators.erase(fd);
    else
	{
        _members.erase(fd);
	}
}

void Channel::clearInvite() { _invite.clear(); }

std::set<int>	Channel::getOperator()	const {return _operators;}

std::set<int>	Channel::getMember()	const {return _members;}

std::set<int>	Channel::getInvite()	const {return _invite;}

std::string 	Channel::getMode()	const {
    std::string mode = " +";
    std::string arg;

    if (_i)
        mode += "i";
    if (_t)
        mode += "t";
    if (_l)
    {
        mode += "l";
        arg = " " + toString(_l);
    }
    if (!_password.empty())
    {
        mode += "k";
        arg += " " + _password;
    }
    if (mode.size() == 2)
        mode.clear();
    return mode + arg;
}


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
	{
        _l = nb;
	}
    else if (c == 'i')
	{
        _i = (nb > 0);
		if (!_i)
			clearInvite();
	}
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

	str += "> invite <";
	for (std::set<int>::iterator it = _invite.begin(); it != _invite.end(); )
	{
		str += toString(*it);
		if ((++it) != _invite.end())
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
