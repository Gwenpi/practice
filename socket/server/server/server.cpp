
#include "server.h"

#define BUFFER_MAX 500

char buffer[BUFFER_MAX] = { 0 };  //������

Server::Server(int af, int type, int protocol ,const char* addr,unsigned int port)
	:m_AF(af),m_Type(type),m_Protocol(protocol),m_Port(port)
{
	initDLL();
	m_BackLog = 50;
	m_Addr = inet_addr(addr);//�����IP��ַ
	m_ServerSock = socket(m_AF, m_Type, m_Protocol);
	memset(&m_SockAddr, 0, sizeof(SOCKADDR));
	m_SockAddr.sin_family = m_AF;
	m_SockAddr.sin_addr.s_addr = m_Addr;
	m_SockAddr.sin_port = htons(m_Port);
	bindSocket();

	//��ʼ����
	listenClient();
}

Server::~Server()
{
	closesocket(m_ServerSock);
	WSACleanup();
}

void Server::bindSocket()
{
	if (m_AF == PF_INET)
	{
		bind(m_ServerSock, (SOCKADDR*)&m_SockAddr, sizeof(SOCKADDR));
	}
	else
	{
		std::cout << "�����ڴ�Э����:" << m_AF << std::endl;
	}
}

void Server::listenClient()
{
	listen(m_ServerSock, m_BackLog);

}

void Server::sendDataToOther()
{
	SOCKADDR clientAddr;
	int nSize = sizeof(SOCKADDR);
	m_ClientSock = accept(m_ServerSock, (SOCKADDR*)&clientAddr, &nSize);

	int strLen = recv(m_ClientSock, buffer, BUFFER_MAX, 0);	//���տͻ��˵�����
	send(m_ClientSock, buffer, strLen, 0);	//ԭ������
	closesocket(m_ClientSock);
	memset(buffer, 0, BUFFER_MAX);
}

void Server::initDLL()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}
