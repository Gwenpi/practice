
#include "server.h"
#include <mutex>

std::mutex mtx;

#define BUFFER_MAX 500
#define CLIENT_MAX 50

char buffer[BUFFER_MAX] = { 0 };  //缓冲区

Server::Server(int af, int type, int protocol ,const char* addr,unsigned int port)
	:m_AF(af),m_Type(type),m_Protocol(protocol),m_Port(port)
{
	m_Addr = inet_addr(addr);//具体的IP地址
	init();

	//开始监听
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
		std::cout << "不存在此协议族:" << m_AF << std::endl;
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
			std::cout << m_Clients.size() << " client 设置非堵塞模式失败!" << std::endl;
			continue;
		}
		Call("accept 加锁");
		mtx.lock();
		m_Clients.push_back(ClientAttri(clientAddr, tempClientSock));//记录以IP为键值的客户端属性
		mtx.unlock();
		Call("连接成功" );
		Call("accept 解锁");
		
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
			int strLen = recv(copyClients[i].m_ClientSock, buffer, BUFFER_MAX, 0);	//接收客户端的数据
			if (strLen>0)
			{
				//Call("写入文件");
				//Call(buffer);
				//for(auto c: copyClients)
				//	send(c.m_ClientSock, buffer, strLen, 0);	//广播
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

