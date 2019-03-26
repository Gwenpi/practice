#pragma once

#pragma warning(disable:4996)
#include<WinSock2.h>
#include<iostream>
#define Call(str) std::cout<<str<<std::endl;


class Server
{
private:
	int m_AF;
	int m_Type;
	int m_Protocol;
	unsigned long m_Addr;
	unsigned int m_Port;
	int m_BackLog;			//������еĳ��ȣ��ܴ�Ŷ��ٵĿͻ�������
	SOCKET m_ServerSock;	
	SOCKET m_ClientSock;	//�����ÿ�ν��տͻ��������õ���ʱ�׽���
	sockaddr_in m_SockAddr;
public:
	Server(int af = PF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, const char* addr = "127.0.0.1",unsigned int port=1234);
	~Server();
	void bindSocket();
	void listenClient();
	void sendDataToOther();	//Ŀǰ��ԭ������
private:
	void initDLL();
};
