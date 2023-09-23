#pragma once
#include "net_common.h"




//header template
// must contain an identifier as unique ip adderess 192.196.441.144
//also implement a uinique identifier with chrono
class NetMessage
{
private:
	std::vector<uint8_t> m_header;
	std::vector<uint8_t> m_message;
	const std::string head_encoder = "sending info % ";

	const std::array<uint8_t, 50> header_valid = { 'a' };
public:
	NetMessage(std::vector<uint8_t> header, std::vector<uint8_t> message) : m_header{ header }, m_message{ message }
	{
	}

	~NetMessage()
	{

	}




	void compose_messge(std::vector<uint8_t> const header, std::vector<uint8_t> const  message)
	{
		m_header = header;
		m_message = message;
	}
	std::vector<uint8_t> get_message()
	{
		return m_message;
	}

	
	size_t size() const
	{
		return m_header.size() + m_message.size();
	}

	
};

