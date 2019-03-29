#pragma once
#pragma warning(disable:4996)
#include<WinSock2.h>


class ClientAttri
{
public:
	sockaddr_in m_SockAddr;
	SOCKET m_ClientSock = INVALID_SOCKET;
	//const char* m_Name = "none";

	ClientAttri() {}
	ClientAttri(const sockaddr_in& addr,const SOCKET& sock/*,const char* name*/):m_SockAddr(addr),m_ClientSock(sock)/*,m_Name(name)*/{}

	inline unsigned long getIP()const { return m_SockAddr.sin_addr.s_addr; }
};