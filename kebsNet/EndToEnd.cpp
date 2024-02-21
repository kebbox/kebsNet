
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
				listen_for_message();
			}
		
			else if (ec == asio::error::operation_aborted) {
				std::cout << "Accept operation aborted: " << ec.message() << std::endl;
				m_server_acceptor.cancel();
			}

			else if (ec == asio::error::eof) {
				std::cout << "connection interrupted by remote pc: " << ec.message() << std::endl;
				m_server_acceptor.cancel();
			}

		
			else 
			{
				std::cout << "ERROR  during asyncAccept: " << ec.message() << std::endl;
				
			}	
		});
	

	
}
void EndToEnd::listen_for_message()
{
	
	//std::vector<char> messageBuffer; // Accumulate the complete message

	//SO I NEED TO PUT  buffer and msg buffer outside the function otherwise they will be recursivly resetted
	//also i need to implement the function message complete ie checking for a termination charater


	m_socket.async_read_some(asio::buffer(buffer), [this ](asio::error_code ec, std::size_t bytes_transferred) {

		if (!ec) {
			// Append the received data to the message buffer
			




			std::string message(buffer.begin(), buffer.begin() + bytes_transferred);
			std::cout << "Received message: " << message << std::endl;
		

			listen_for_message();

		}
		else if (ec == asio::error::eof) {
			std::cout << "connection interrupted by remote pc: " << ec.message() << std::endl;
			m_server_acceptor.cancel();
		}
		else if (ec != asio::error::not_connected) {
			std::cout << "Error during message reception: " << ec.message() << std::endl;
			// Handle the error as appropriate
		}
		});
	

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
		
		std::cout << message << std::endl;
		asio::const_buffer buffer = asio::buffer(message);
		asio::write( m_socket, buffer, ec);

		if (!ec)
		{
			std::cout << "message delivered" << std::endl;

		}
		else {
			std::cout << "error sending message " << ec.message() << std::endl;

		}
	
	
}


void EndToEnd::clear_message()
{
	//simply reset message to a nullptr
	m_message = nullptr;
}





void EndToEnd::run_context() {
	m_client_context.run();
}

void EndToEnd::stop_context() {
	m_client_context.stop();
}
