#include "client.h"
#include<iostream>

#define BUFFER_MAX 500

char bufSend[BUFFER_MAX] = { 0 };
char bufRecv[BUFFER_MAX] = { 0 };

#define Call(str) std::cout<<str<<std::endl;

Client::Client(int af, int type, int protocol, const char * addr, unsigned int port)
	:m_AF(af), m_Type(type), m_Protocol(protocol), m_Port(port)
{
	initDLL();
	m_Addr = inet_addr(addr);

	
	//初始化m_SockAddr
	memset(&m_SockAddr, 0, sizeof(SOCKADDR));
	m_SockAddr.sin_family = m_AF;
	m_SockAddr.sin_addr.s_addr = m_Addr;
	m_SockAddr.sin_port = htons(m_Port);
}

Client::~Client()
{
	WSACleanup();
}

void Client::sendData()
{
	m_ClientSock = socket(m_AF, m_Type, m_Protocol);
	connect(m_ClientSock, (SOCKADDR*)&m_SockAddr, sizeof(SOCKADDR));
	std::cout << "输入： " << std::endl;
	std::cin >> bufSend;
	send(m_ClientSock, bufSend, strlen(bufSend), 0);
	recv(m_ClientSock, bufRecv, BUFFER_MAX, 0);
	std::cout << "接收到的内容: " << bufRecv << std::endl;

	memset(bufSend, 0, BUFFER_MAX);
	memset(bufRecv, 0, BUFFER_MAX);
	closesocket(m_ClientSock);
}

void Client::receiveData()
{
	
}

void Client::initDLL()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

}
