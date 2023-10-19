#include "Core.h"
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

std::string helpMap()
{
	std::string help = "Welcome to the help section!\n "
		" currently the app is under development \n"
		" try the following inputs: \n"
		" '-help' display this message\n"
		" '-make connection <ip, port>' \n"
		" '-send message <message>'\n"
		" '-listen for connection <port>'\n"
		" '-break connection'\n";
		" '-quit' end this program";
		" 'stop listening' stop listen for connection";
	return help;
}

uint16_t custom_converter(std::string input)
{
	//hardcoding conversion for string input
	//adding a check for invalid input
	std::string numbers = "1234567890"; 
	
	if (input.back() == ' '){
		input.pop_back();
	
	}
	for (auto i : input ) {
		if (numbers.find(i) == std::string::npos) {
			std::cout << "error invalid port!" << std::endl;
			return 0;
		}
	}
	int partial = stoi(input);
	return static_cast<uint16_t>(partial);

}

std::string ignore_spaces(std::string name) {
	if (name.find(' ')) {

		 name.erase(std::remove(name.begin(), name.end(), ' '), name.end());	
		 return name;
	}
}

void usr_make_connection(EndToEnd& istance, std::string ip,  uint16_t port)
{
	
	//here i add a check for the ip address
	
	if (ip.length() != 13) {
		std::cout << "error: invalid ip address" << std::endl;
		
	}
	
	else  {
		std::thread io_thread([&istance, port, ip] {
			istance.make_connection(ip, port);
			});
		io_thread.detach();

		std::cout << "tring to connect to:  " << ip << std::endl;
		
	}
}


void usr_send_message(const std::string& message, EndToEnd& istance)
{
	NetMessage user_message;
	user_message.compose_messge(message);

	istance.send_message(user_message);

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
		
		std::thread io_thread([&istance, &port] {
			istance.wait_for_connection(port);
			});

		io_thread.detach();
		std::cout << "started listening for connection" << std::endl;
		flg.acceptor = true;
	}
}

void stop_listening(EndToEnd& istance)
{
	istance.stop_waiting();
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
	const std::unordered_map<std::string, Inputs> input_map
	{
		{"help", Inputs::help},
		{"make connection ", Inputs::makeConn},
		{"listen for connection ", Inputs::listenForConn},
		{"send message", Inputs::sendMessage},
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
				std::cout << helpMap();

				break;

			case Inputs::makeConn:
				val = custom_converter(tokens[2]); 
				if (val == 0) break; 
				
				ip = ignore_spaces(tokens[1]);

				usr_make_connection( *sharedEt, ip, val);

				break;

			case Inputs::listenForConn:
				val = custom_converter(tokens[1]); 
				if (val == 0) break;
				usr_listen_connection(*sharedEt, flg, val);

				break;

			case Inputs::sendMessage:
				usr_send_message(tokens[1], *sharedEt);

				break;

			case Inputs::breakConn:
				usr_break_connection(*sharedEt);

				break;
			case Inputs::quit:
				destroyEt = true;
				loop = false;
				
				break;

			case Inputs::stopListening:
				stop_listening(*sharedEt);
				destroyEt = true;
				std::cout << "stopped listening to connection " << std::endl;
				break;
			}
		}
	}

	sharedEt->stop_context();
	sharedEt.reset();

}

