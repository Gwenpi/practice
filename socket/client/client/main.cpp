#include"client.h"

int main()
{
	Client client;
	while (true)
	{
		client.sendData();
		client.receiveData();
	}

	return 0;
}