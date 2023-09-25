#pragma once

#include "net_common.h"
#include "NetMessage.h"

class EndToEnd
{
private:

	
	asio::error_code m_client_ec;
	asio::io_context m_client_context;
	
	asio::io_context m_server_context;
	asio::ip::tcp::acceptor m_server_acceptor;

	asio::ip::tcp::socket m_socket;
	asio::ip::tcp::endpoint m_endpoint;

	//passing a message pointer for every message sent
	NetMessage * m_message;

public:
	EndToEnd(uint16_t port)
		: m_server_acceptor(m_server_context),
		m_endpoint(asio::ip::tcp::v4(), port),
		m_message{ nullptr },
		m_socket(m_client_context)
		
		
	{

	};
	//make this func async until a connection is established
	void wait_for_connection() 
	{
	
	}

	void make_connection(std::string ip, uint16_t port)
	{
		asio::ip::tcp::endpoint  endpoint(asio::ip::make_address(ip, m_client_ec), port);
		
		m_socket.connect(endpoint, m_client_ec);
		if (!m_client_ec) {
			std::cout << "connected" << std::endl;
		}
		else
		{
			std::cout << "failed to connect to address " << m_client_ec.message();
		}

		if (m_socket.is_open()) {
			on_connection();
		}

	}
	//all of this part must be async with read and write
	//also will contain a check for header and possible key encr
	//in the future

	//allow messages if connected
	bool on_connection()
	{
		return true;

	}

	void send_message( NetMessage* message)
	{

			std::vector<uint8_t> msg = message->get_message();
			asio::error_code ec;
			m_socket.write_some(asio::buffer(msg.data(), msg.size()), ec);
			
					if (!ec)
					{
						std::cout << "message delivered" << std::endl;

					}
					else if (ec) {
						std::cout << "error sending message " << ec.message() << std::endl;

					
				}
		

	}

	void clear_message()
	{
		//simply reset message to a nullptr
		m_message = nullptr;
	}

	void listen_for_message()
	{
		size_t bites = m_socket.available();
		if (bites > 0) {
			std::vector<char> buffer(1024); 
			
				
			m_socket.async_read_some(asio::buffer(buffer.data(), buffer.size()),[buffer, this](asio::error_code ec, std::size_t message_bytes) {
				if (!ec)
				{
					std::string message(buffer.begin(), buffer.begin() + message_bytes);
					std::cout << "message : " << message << std::endl;
					listen_for_message();
				}
				else if (ec)
				{
					std::cout << "Error durig message reception: " << ec.message() << std::endl;
					
				}

				});
		}

	}

};

