#include "EndToEnd.h"


// ok looks like i need a timer for async acceptor 
// an expiration timer
void EndToEnd::wait_for_connection(uint16_t port)
{
	//looks like that the async asio operation are hard to kill
	// so if the user want to close the listening for connection i must destroy the whole object
	// 

	asio::ip::tcp::endpoint acceptor_endpoint(asio::ip::tcp::v4(), port);
	m_server_acceptor.open(acceptor_endpoint.protocol());
	m_server_acceptor.bind(acceptor_endpoint);
	m_server_acceptor.listen();
	bool flag = true;

	m_server_acceptor.async_accept(m_server_socket,
		[this](const asio::error_code& ec) {
			
			if (!ec)
			{
				std::cout << "connection accepted! " << std::endl;
			}
		
	
			else if(ec)
			{
				std::cout << "ERROR  during asyncAccept: " << ec.message() << std::endl;
				
			}	
		});
	run_context();
	
}

void EndToEnd::stop_waiting()
{
}


void EndToEnd::make_connection(const std::string ip, uint16_t port)
{
	asio::ip::tcp::endpoint  endpoint(asio::ip::make_address(ip), port);

	m_socket.async_connect(endpoint, [this](asio::error_code ec)
		{
			if (!ec) {
				std::cout << std::endl << "connected" << std::endl;
			}

			else
			{
				std::cout << std::endl << ec.message()<< std::endl;
			}
	
		});
	run_context();

}


void EndToEnd::close_connection()
{

}


bool EndToEnd::on_connection()
{
	return true;

}


void EndToEnd::send_message(NetMessage& message)
{
	if (m_connection) {
		std::string msg = message.get_message();
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
	else
	{
		std::cout << "Error cannot send message if client is not connected" << std::endl;
	}
}


void EndToEnd::clear_message()
{
	//simply reset message to a nullptr
	m_message = nullptr;
}


void EndToEnd::listen_for_message()
{
	size_t bites = m_socket.available();
	if (bites > 0) {
		std::vector<char> buffer(1024);


		m_socket.async_read_some(asio::buffer(buffer.data(), buffer.size()), [buffer, this](asio::error_code ec, std::size_t message_bytes) {
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


void EndToEnd::run_context() {
	m_client_context.run();
}

void EndToEnd::stop_context() {
	m_client_context.stop();
}
