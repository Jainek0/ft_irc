# ft_irc


## struct :
```cpp
class server :
{

	forme cannonique...

	private:
		std::map<int(fd_client), 			Client> 	_clients;
		std::map<std::string(name_channel),	Channel> 	_channels;
		size_t 											_pid
		std::string 									_pasword

	public:
		void acceptClient();
		void removeClient(int fd);
		void handleCommand(int fd, std::string cmd);
};
```

```cpp
class client :
{
	private:
		std::string 	_password;

	public:
		int 			fd;
		std::string 	nick;
		std::string 	username;
		bool 			authenticated;
}

```cpp
class channel :
{
	private:
		std::set<int> 	_members;
		std::set<int> 	_operators;
		std::string 	_channel_name
		std::string 	_pasword
		bool			_i
		bool			_t
		int				_l

	void bultin_[...](std::string str);

	[
		∗ KICK - Eject a client from the channel
		∗ INVITE - Invite a client to a channel
		∗ TOPIC - Change or view the channel topic
		∗ MODE - Change the channel’s mode:
			· i: Set/remove Invite-only channel
			· t: Set/remove the restrictions of the TOPIC command to channel
			operators
			· k: Set/remove the channel key (password)
			· o: Give/take channel operator privilege
			· l: Set/remove the user limit to channel
	]
}

```

