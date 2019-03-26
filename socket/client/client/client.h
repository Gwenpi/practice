#pragma once
#pragma warning(disable:4996)
#include<WinSock2.h>

class Client
{
private:
	int m_AF;
	int m_Type;
	int m_Protocol;
	unsigned long m_Addr;
	unsigned int m_Port;
	//SOCKET m_ServerSock;//客户端似乎不用监听服务端
	sockaddr_in m_SockAddr;	
	SOCKET m_ClientSock;	
public:
	Client(int af = PF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, const char* addr = "127.0.0.1", unsigned int port = 1234);
	~Client();
	void sendData();
	void receiveData();
private:
	void initDLL();

};
