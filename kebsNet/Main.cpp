#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#include "net_common.h"
#include "EndToEnd.h"
#include "NetMessaage.h"





int main()
{
	uint16_t port = 4000;
	

	 EndToEnd istance(565);
	 istance.make_connection("192.168.1.1", 566);
	 std::vector<uint8_t> expl_msg = { 'C','A','C','A'};
	 NetMessage msg(expl_msg, expl_msg);	
	 istance.send_message(&msg);

	// ----- CLIENT LIKE PROGRAM ----
	//this is basiclly what i need to initialize a tcp connection
	//as the endpoint is endled by the resolve function (ip, conn name)
	
	
	/*
	asio::error_code ec;
	asio::io_context context;
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("192.168.1.105",ec),80);

	//this binds the context to a socket and then connect the things
	asio::ip::tcp::socket socket(context);
	socket.connect(endpoint, ec);
	if (!ec) {
		std::cout << "connected" << std::endl;

	}
	else std::cout << "failed " << ec.message();

	*/
	
	return 0;
}

