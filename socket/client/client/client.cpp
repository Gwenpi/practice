#include "client.h"
#include<iostream>
#include<time.h>

#define BUFFER_MAX 500

char bufSend[BUFFER_MAX] = { 0 };
char bufRecv[BUFFER_MAX] = { 0 };

#define Call(str) std::cout<<str<<std::endl;
/*
Client::Client(const char * addr, unsigned int port,int af, int type, int protocol)
	:m_Addr(inet_addr(addr)), m_AF(af), m_Type(type), m_Protocol(protocol), m_Port(port)
{
	initDLL();
	m_Message = new Message("message/group_chat_client.txt");
	//初始化m_SockAddr
	memset(&m_SockAddr, 0, sizeof(SOCKADDR));
	m_SockAddr.sin_family = m_AF;
	m_SockAddr.sin_addr.s_addr = m_Addr;
	m_SockAddr.sin_port = htons(m_Port);

	m_ClientSock = socket(m_AF, m_Type, m_Protocol);

	connect(m_ClientSock, (SOCKADDR*)&m_SockAddr, sizeof(SOCKADDR));
}
*/


Client::Client(const char* filePath)
{
	initDLL();
	m_Message = new Message(filePath);
	//初始化m_SockAddr
	memset(&m_SockAddr, 0, sizeof(SOCKADDR));
	m_SockAddr.sin_family = m_AF;
	m_SockAddr.sin_addr.s_addr = m_Addr;
	m_SockAddr.sin_port = htons(m_Port);

	m_ClientSock = socket(m_AF, m_Type, m_Protocol);

	connect(m_ClientSock, (SOCKADDR*)&m_SockAddr, sizeof(SOCKADDR));
}

Client::~Client()
{	
	send(m_ClientSock, bufSend, strlen(bufSend), 0);
	delete m_Message;
	closesocket(m_ClientSock);
	WSACleanup();
}

void Client::sendData()
{
	while (true)
	{
		//connect(m_ClientSock, (SOCKADDR*)&m_SockAddr, sizeof(SOCKADDR));//只连接一次
		srand(unsigned int(time(0)));
		int number = std::rand() % 5;
		std::string str;
		switch (number)
		{
			case 0:str = "0"; break;
			case 1:str = "1"; break;
			case 2:str = "2"; break;
			case 3:str = "3"; break;
			case 4:str = "4"; break;
		};
		//std::cout << "输入： " << std::endl;
		//std::cin >> bufSend;
		
		send(m_ClientSock, str.c_str(), str.size(), 0);
		memset(bufSend, 0, BUFFER_MAX);
	}	
}

void Client::receiveData()
{
	while (true)
	{
		recv(m_ClientSock, bufRecv, BUFFER_MAX, 0);
		//std::cout << "接收消息并写入log"<< std::endl;
		if(bufRecv[0]!='\0')
			m_Message->addMessage(bufRecv);
		memset(bufRecv, 0, BUFFER_MAX);
	}
}

void Client::initDLL()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

}
