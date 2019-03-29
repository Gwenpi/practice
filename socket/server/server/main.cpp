
#include"server.h"
#include <thread>


int main()
{
	
	Server server;
	std::thread t1(&Server::acceptConnect,&server);
	std::thread t2(&Server::sendData,&server);
	t1.join();
	t2.join();


	return 0;
}