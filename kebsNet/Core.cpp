#include "Core.h"


void usr_make_connection(EndToEnd& istance, std::string ip,  uint16_t port)
{
	
	//here i add a check for the ip address
	
		std::thread io_thread([&istance, port, ip] {
			istance.make_connection(ip, port);
			});
		io_thread.detach();

		std::cout << "tring to connect to:  " << ip << std::endl;
		
	
}


void usr_send_message(const std::string& message, EndToEnd& istance)
{
	

	istance.send_message(message);

	//ok
}


void usr_break_connection(EndToEnd& istance)
{
	istance.close_connection();
}


void usr_listen_connection(EndToEnd& istance, stopping_flags &flg, uint16_t port)
{
	//ok this mutex dont  work because is detached
	//
	if (flg.acceptor) {
		std::cout << "Already listening for connection!" << std::endl;
	}

	else if (!flg.acceptor) {
		
		std::thread io_thread([&istance, port] {
			istance.wait_for_connection(port);
			});

		io_thread.detach();
		std::cout << "started listening for connection" << std::endl;
		flg.acceptor = true;
	}
}

//TO HERE  i will just implement everithing in the class or via external 
// function for extra needs
// all the class method will be directily called in the switch statment
//so it will be more clear

std::vector<std::string> input_tokenizer(std::string word)
{
	const char delimiter = '-';
	std::stringstream string_stream(word);
	std::vector<std::string> tokens;

	while (!string_stream.eof())
	{
		std::getline(string_stream, word, delimiter);
		tokens.push_back(word);
	}
	return tokens;

}

void reset_flags(stopping_flags& flg)
{
	flg.acceptor = false;
	
}

void user_input()
{
	enum class Inputs
	{
		help,
		makeConn,
		listenForConn,
		sendMessage,
		breakConn,
		quit,
		stopListening

	};


	const std::unordered_map<std::string, Inputs> input_map
	{
		{"help", Inputs::help},
		{"make connection ", Inputs::makeConn},
		{"listen for connection ", Inputs::listenForConn},
		{"send message ", Inputs::sendMessage},
		{"break connection", Inputs::breakConn},
		{"quit", Inputs::quit},
		{"stop listening", Inputs::stopListening}

	};

	stopping_flags flg{ false };

	//HERE I NEED TO USE A SEPARATE THREAD
	//othewise asio will run and will block the user input loop
	std::shared_ptr<EndToEnd> sharedEt = std::make_shared<EndToEnd>();

	bool loop = true;
	bool destroyEt = false;

	uint16_t val;
	std::string ip ="";
	std::string converted_msg = "";

	while (loop) {

		if (destroyEt) {
			sharedEt->stop_context();
			sharedEt.reset();
			destroyEt = false;
			sharedEt = std::make_shared<EndToEnd>();
			reset_flags(flg);
		}
		


		std::string usr_input = "";
		std::cout << ">";
		std::cin.clear();

		std::getline(std::cin, usr_input);

		std::vector<std::string> tokens = input_tokenizer(usr_input);

		auto match = input_map.find(tokens[0]);

		

		if (match == input_map.end() && usr_input != "\r\n")
		{
			std::cout << "wrong input, try to type '-help' to see all possible inputs" << std::endl;

		}

		else
		{
			switch (match->second)
			{
			case Inputs::help:
				std::cout << utils::helpMap();
				break;

				// here i handle specific input like port and ip address , for valuating those input
				//i use custom functions
			case Inputs::makeConn:
				val = utils::custom_converter(tokens[2]); 
				if (val == 0) break; 
				ip = utils::ignore_spaces(tokens[1]);

				usr_make_connection( *sharedEt, ip, val);
				break;

			case Inputs::listenForConn:
				val = utils::custom_converter(tokens[1]); 
				if (val == 0) break;
				usr_listen_connection(*sharedEt, flg, val);

				break;

			case Inputs::sendMessage:
				//here i have a problem , if the user use "-" char inside the message i will encounter a error
				//i need a way to fix this problem
				converted_msg = utils::message_converter(tokens[1]);
				if (converted_msg != "@#$%%575339") {
					usr_send_message(converted_msg, *sharedEt);
					break;
				}
				else {
					std::cout << "invalid message format try again";
					break;
				}
				

			case Inputs::breakConn:
				sharedEt->close_connection();

				std::cout << "connection interrupted " << std::endl;
				break;

			case Inputs::quit:
				destroyEt = true;
				loop = false;
				break;

			case Inputs::stopListening:
				sharedEt->stop_waiting();
				destroyEt = true;
				std::cout << "stopped listening to connection " << std::endl;
				break;
			}
		}
	}

	sharedEt->stop_context();
	sharedEt.reset();

}

