#pragma once
#pragma warning(disable:4996)
#include<WinSock2.h>
#pragma comment (lib, "ws2_32.lib") 
#include"message.h"

class Client
{
private:
	int m_AF= PF_INET;
	int m_Type= SOCK_STREAM;
	int m_Protocol= IPPROTO_TCP;
	unsigned long m_Addr= inet_addr("127.0.0.1");
	unsigned int m_Port=1234;
	//SOCKET m_ServerSock;//客户端似乎不用监听服务端
	sockaddr_in m_SockAddr;	
	SOCKET m_ClientSock;
	Message* m_Message;
public:
	Client(const char* filePath);
	//Client(const char* addr = "127.0.0.1", unsigned int port = 1234,int af = PF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	~Client();
	void sendData();
	void receiveData();
private:
	void initDLL();

};
