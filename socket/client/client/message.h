#pragma once
#include<iostream>
#include<fstream>
#include<string>

class Message
{
private:
	const char* m_FilePath;
	std::fstream m_FileStream;
public:
	Message(const char* path = nullptr);
	void addMessage(const std::string& message);
	void clearMessage();
private:
	void readFile();
};
