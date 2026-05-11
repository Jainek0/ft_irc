# ft_irc

1. le main creer un serveur.
```cpp 
pid_serv, password_serv
```

2. le serveur ecoute sont pid et attend des instruction.

3. quand un un client se connecte, le serveur demande au client de sidentifier avec le password_serv.

4. le serve ajoute un client a ca liste, avec les inforamtion de base.
```cpp 
pid_client, username, nick
```

5. un client peut creer/rejoindre un channel. 
```cpp 
name_channel
```

6. un channel utilise c est variable interne pour l administartion du channel. le premier a rejoindre le channelle est ajouter dans la liste des operators, les suivant dans la liste members. 

7. un client peut interagir avec un channel. 

8. si un client fat partie de la liste operateur du channel il a des droit d administrator.

9. un user peut etre bouger de la liste operator a menber seulement par un operator du channel concerne.

10. la liste operator d un channel ne peut pas etre vide. 


## struct :
```cpp
class Server
{

	forme cannonique...

	private:
		std::map<int(fd_client), 			Client> 	_clients;
		std::map<std::string(name_channel),	Channel> 	_channels;
		int 											_pid;
		std::string 									_pasword;

	public:
		void acceptClient();
		void removeClient(int fd);
		void handleCommand(int fd, std::string cmd);
};
```

```cpp
class Client
{
	public:
		int 			fd;
		std::string 	nick;
		std::string 	username;
		bool 			authenticated;
};
```

```cpp
class Channel
{
	private:
		std::set<int> 	_members;
		std::set<int> 	_operators;
		std::string 	_channel_name;
		std::string 	_pasword;
		bool			_i;
		bool			_t;
		int				_l;

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
};

```

