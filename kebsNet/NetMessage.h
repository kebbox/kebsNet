#pragma once
#include "net_common.h"



// i made this class for future implementation like checking for header
// timing and encryption for now it has not really a porpouse
class NetMessage
{
private:
	std::vector<uint8_t> m_header;
	std::string m_message;
	const std::string head_encoder = "sending info % ";

	const std::array<uint8_t, 50> header_valid = { 'a' };
public:
	NetMessage(std::string message) : m_message{ message }
	{
	}

	NetMessage()
	{

	}

	~NetMessage()
	{

	}


	void compose_messge(const std::string &message)
	{
		m_message = message;
	}

	std::string get_message()
	{
		return m_message;
	}

	
	size_t size() const
	{
		return m_header.size() + m_message.size();
	}

	
};

