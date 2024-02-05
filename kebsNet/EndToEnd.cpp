
#include "EndToEnd.h"


// ok looks like i need a timer for async acceptor 
// an expiration timer
void EndToEnd::listen_for_connection(uint16_t port)
{
	//looks like that the async asio operation are hard to kill
	// so if the user want to close the listening for connection i must destroy the whole object
	// 
	
	asio::ip::tcp::endpoint acceptor_endpoint(asio::ip::tcp::v4(), port);
	m_server_acceptor.open(acceptor_endpoint.protocol());
	m_server_acceptor.bind(acceptor_endpoint);
	m_server_acceptor.listen();
	bool flag = true;

	m_server_acceptor.async_accept(m_socket,
		[this](const asio::error_code& ec) {
			
			if (!ec)
			{
				std::cout << "connection accepted! " << std::endl;
				
				
				this->listen_for_message();
					
				
				
			}
		
	
			else if(ec)
			{
				std::cout << "ERROR  during asyncAccept: " << ec.message() << std::endl;
				
			}	
		});
	run_context();
	
}

void EndToEnd::stop_listening()
{
}


void EndToEnd::make_connection(const std::string ip, uint16_t port)
{
	asio::ip::tcp::endpoint  endpoint(asio::ip::make_address(ip), port);
	
	m_socket.async_connect(endpoint, [this](asio::error_code ec)
		{
			if (!ec) {
				std::cout << std::endl << "connected" << std::endl;
				//ok this work i dont need to make the listen for message also in a separete thread
				//thinking about it it make sense beacuse make connection is already in a separete thread
				//the same in the function listen for connection
				this->listen_for_message();
					
				
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


void EndToEnd::send_message(std::string message)
{
	
		
		asio::error_code ec;
		message.append("\0");
		std::cout << message << std::endl;
		asio::const_buffer buffer = asio::buffer(message);
		m_socket.write_some(buffer, ec);

		if (!ec)
		{
			std::cout << "message delivered" << std::endl;

		}
		else if (ec) {
			std::cout << "error sending message " << ec.message() << std::endl;

		}
	
	
}


void EndToEnd::clear_message()
{
	//simply reset message to a nullptr
	m_message = nullptr;
}


void EndToEnd::listen_for_message()
{
	std::vector<char> buffer(1024); // Initial buffer size 
	std::vector<char> messageBuffer; // Accumulate the complete message

	//SO I NEED TO PUT  buffer and msg buffer outside the function otherwise they will be recursivly resetted
	//also i need to implement the function message complete ie checking for a termination charater
	std::cout << "open for messages " << std::endl;
	
		m_socket.async_read_some(asio::buffer(buffer), [this, &messageBuffer, &buffer](asio::error_code ec, std::size_t bytes_transferred) {
			
			if (!ec) {
				// Append the received data to the message buffer
				;
				// Check if the message is complete (e.g., by checking for message termination)
				if (utils::is_message_complete(messageBuffer)) {
					std::string message(messageBuffer.begin(), messageBuffer.end());
					std::cout << "Received message: " << message << std::endl;
					// Clear the message buffer for the next message
					messageBuffer.clear();
				}
				listen_for_message();
	
			}
			else {
				std::cout << "Error during message reception: " << ec.message() << std::endl;
				// Handle the error as appropriate
			}
			});
		run_context();
	
	

}



void EndToEnd::run_context() {
	m_client_context.run();
}

void EndToEnd::stop_context() {
	m_client_context.stop();
}
