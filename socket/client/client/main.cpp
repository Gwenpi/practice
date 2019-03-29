#include"client.h"
#include<thread>
#include<iostream>

#include<string>


int main()
{

	std::string filePath;
	std::cout << "please input filePath:" << std::endl;
	std::cin >> filePath;

	Client client(filePath.c_str());
	std::thread t2(&Client::receiveData, &client);
	std::thread t1(&Client::sendData, &client);
	t1.join();
	t2.join();



	return 0;
}