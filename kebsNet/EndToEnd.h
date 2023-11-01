#pragma once

#include "net_common.h"
#include "NetMessage.h"

class EndToEnd
{
private:

	
	asio::error_code m_client_ec;
	asio::io_context m_client_context;
	
	
	asio::ip::tcp::acceptor m_server_acceptor;

	asio::ip::tcp::socket m_socket;
	asio::ip::tcp::endpoint m_endpoint;

	uint16_t port = 0;

	asio::ip::tcp::socket m_server_socket;
	bool m_connection = false;

	std::mutex m_acceptor_mutex;
	


	

	//passing a message pointer for every message sent
	NetMessage * m_message;

	//ok some things that need to be cleared up
	
	// -- Error messages are a mess i should create a single istance
	//or separate each message per function

	//--another issue reguards async handling and the fact that im
	//using just one io_context
	//should also find a whay to organize thread

public:

	

	EndToEnd(uint16_t port = 200)
		: m_server_acceptor(m_client_context),
		m_endpoint(asio::ip::tcp::v4(), port),
		m_message{ nullptr },
		m_socket(m_client_context),
		m_server_socket(m_client_context) {};
	

	//bunch of fundamental function for networking
	void wait_for_connection(uint16_t port);
	
	void stop_waiting();

	void make_connection(const std::string ip, uint16_t port);

	void close_connection();

	bool on_connection();

	void send_message(std::string message);

	void clear_message();

	void listen_for_message();

	void run_context();

	void EndToEnd::stop_context();


	//this function "set flag" change the flag if i want to interrupt an 
	//async operation i used a enum just for semplicity
	//not the prettiest idea

};

