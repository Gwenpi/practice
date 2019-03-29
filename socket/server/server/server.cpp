
#include "server.h"
#include <mutex>

std::mutex mtx;

#define BUFFER_MAX 500
#define CLIENT_MAX 50

char buffer[BUFFER_MAX] = { 0 };  //������

Server::Server(int af, int type, int protocol ,const char* addr,unsigned int port)
	:m_AF(af),m_Type(type),m_Protocol(protocol),m_Port(port)
{
	m_Addr = inet_addr(addr);//�����IP��ַ
	init();

	//��ʼ����
	listen(m_ServerSock, LISTEN_SIZE);
}

Server::~Server()
{
	delete m_Message;
	closesocket(m_ServerSock);
	WSACleanup();
}

void Server::bindSocket(const sockaddr_in& addr)
{
	if (m_AF == PF_INET)
	{
		bind(m_ServerSock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	}
	else
	{
		std::cout << "�����ڴ�Э����:" << m_AF << std::endl;
	}
}

void Server::acceptConnect()
{
	while (true)
	{
		sockaddr_in clientAddr;
		int nSize = sizeof(SOCKADDR);
		
		SOCKET tempClientSock;
		tempClientSock = accept(m_ServerSock, (SOCKADDR*)&clientAddr, &nSize);
		unsigned long ul = 1;
		int ret = ioctlsocket(tempClientSock, FIONBIO, (unsigned long*)&ul);
		if (ret == SOCKET_ERROR)
		{
			std::cout << m_Clients.size() << " client ���÷Ƕ���ģʽʧ��!" << std::endl;
			continue;
		}
		Call("accept ����");
		mtx.lock();
		m_Clients.push_back(ClientAttri(clientAddr, tempClientSock));//��¼��IPΪ��ֵ�Ŀͻ�������
		mtx.unlock();
		Call("���ӳɹ�" );
		Call("accept ����");
		
	}
}

void Server::sendData()
{
	std::vector<ClientAttri>copyClients;
	while (true)
	{	
		mtx.lock();
		
		if (copyClients.size() != m_Clients.size())
		{
			copyClients.clear();
			for (int i = 0; i < m_Clients.size(); i++)
				copyClients.push_back(m_Clients[i]);
		}
		mtx.unlock();

		//std::vector<ClientAttri>copyClients;
		//copyClients.assign(m_Clients.begin(), m_Clients.end());
		/*
		int clientsSize = m_Clients.size();
		ClientAttri* copyClients[CLIENT_MAX];
		for (int i=0;i<clientsSize;i++)
		{
			copyClients[i] = &m_Clients[i];
		}
		*/
		for (int i = 0; i < copyClients.size(); i++)
		{
			int strLen = recv(copyClients[i].m_ClientSock, buffer, BUFFER_MAX, 0);	//���տͻ��˵�����
			if (strLen>0)
			{
				//Call("д���ļ�");
				//Call(buffer);
				//for(auto c: copyClients)
				//	send(c.m_ClientSock, buffer, strLen, 0);	//�㲥
				for (int j = 0; j < copyClients.size(); j++)
				{
					send(copyClients[j].m_ClientSock, buffer, strLen, 0);
				}
			}

			memset(buffer, 0, BUFFER_MAX);
		}
		
		//closesocket(m_ClientSock);
		//shutdown(m_ClientSock);
		
	}
}

/*
void Server::sendDataToOther()
{

	
}
*/

void Server::init()
{
	m_Message = new Message("message/group_chat.txt");
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	


	m_ServerSock = socket(m_AF, m_Type, m_Protocol);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(SOCKADDR));
	sockAddr.sin_family = m_AF;
	sockAddr.sin_addr.s_addr = m_Addr;
	sockAddr.sin_port = htons(m_Port);
	bindSocket(sockAddr);
}

