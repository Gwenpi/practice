#pragma once

#pragma warning(disable:4996)
#include<WinSock2.h>
#include<iostream>
#pragma comment (lib, "ws2_32.lib") 

#include"client_attr.h"
#include"message.h"
#include<vector>

#define Call(str) std::cout<<str<<std::endl;

#define LISTEN_SIZE 20

class Server
{
private:
	int m_AF=0;
	int m_Type=0;
	int m_Protocol=0;
	unsigned long m_Addr=0;
	unsigned int m_Port=0;
	std::vector<ClientAttri>m_Clients;
	SOCKET m_ServerSock = INVALID_SOCKET;
	Message* m_Message;
public:
	Server(int af = PF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, const char* addr = "127.0.0.1",unsigned int port=1234);
	~Server();
	void bindSocket(const sockaddr_in& addr);

	void acceptConnect();
	void sendData();	//目前是原样返回
private:
	void init();
};
