#include "message.h"


Message::Message(const char * path)
	:m_FilePath(path)
{
}

void Message::addMessage(const std::string & message)
{
	m_FileStream.open(m_FilePath, std::ios_base::in | std::ios_base::out| std::ios_base::app);
	if (!m_FileStream.is_open())
	{
		std::cout << m_FilePath << " open fail £¡" << std::endl;
	}
	m_FileStream << message << std::endl;
	m_FileStream.close();
}

void Message::clearMessage()
{
	m_FileStream.open(m_FilePath, std::ios_base::out);
	if (!m_FileStream.is_open())
	{
		std::cout << m_FilePath << " open fail £¡" << std::endl;
	}
	m_FileStream.clear();
	//m_FileStream.close();

}

void Message::readFile()
{
	m_FileStream.open(m_FilePath, std::ios_base::in);
	if (!m_FileStream.is_open())
		std::cout << m_FilePath << " open fail!" << std::endl;

}
