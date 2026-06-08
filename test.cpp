#include <iostream>
#include <string>
#include <set>
#include <map>

<<<<<<< HEAD
#include "src/_header/irc.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "nop";
		return 0;
	}

    Server&  serv = Server::getInstance(3232, "pass");

	int pid(4242);
    serv.acceptClient();
	argv++;
	while (*argv)
	{
		if (serv.checkClient(pid))
			   Command::handleCommand((serv.findClient(pid))->second, *argv++);
	}
	

    std::string str = argv[1];
	return 0;
=======
class	Client
{
	public:
		client(int fd):_fd(fd){std::cout<<"new client"<<std::endl;}
		~client(void){std::cout<<"new client"<<std::endl;}

		const int	getFd(void)const{return(_fd);}
	private:
		int	_fd;
};

int	main(void)
{
	std::map<int, Client>	clientfd;
	Client client1(1);
	Client client2(2);
	Client client3(3);

	clientfd.insert({1, client1});
	clientfd.insert({3, client3});
	clientfd.insert({5, client(5)});

	std::cout << clientfd[1] << std::endl;
>>>>>>> agamay_server
}