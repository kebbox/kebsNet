#include <iostream>
#include <unordered_map>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#include "net_common.h"
#include "EndToEnd.h"
#include "NetMessage.h"

enum class Inputs
{
	help,
	makeConn,
	listenForConn,
	sendMessage,
	breakConn,
	quit

};

std::string helpMap()
{
	std::string help = "Welcome to the help section!/n "
		" currently the app is under development /n"
		" try the following inputs: /n"
		" '-help' display this message/n"
		" '-make connection <ip, port>' /n"
		" '-send message <message>'/n"
		" '-listen for connection'/n"
		" '-break connection'/n";
	return help;
}

uint16_t custom_converter(std::string input)
{
	//hardcoding conversion for string input
	int partial = stoi(input);
	return static_cast<uint16_t>(partial);
}


//all of this function are just usless FROM HERE
void usr_make_connection(const std::string ip, const uint16_t port
	, EndToEnd &istance)
{
	//check for input errors
	//ip must be ok
	istance.make_connection(ip, port);
}


void usr_send_message(const std::string &message , EndToEnd& istance)
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


void usr_listen_connection(EndToEnd& istance)
{

}

//TO HERE  i will just implement everithing in the class or via external 
// function for extra needs
// all the class method will be directily called in the switch statment
//so it will be more clear

std::vector<std::string> input_tokenizer(std::string word)
{
	const char delimiter = ' ';
	std::stringstream string_stream(word);
	std::vector<std::string> tokens;

	while (!string_stream.eof()) 
	{
		std::getline(string_stream, word, delimiter);
		tokens.push_back(word);
	}
	return tokens;

}

void user_input()
{
	const std::unordered_map<std::string, Inputs> input_map
	{
		{"-help", Inputs::help},
		{"-make connection", Inputs::makeConn},
		{"-listen for connection", Inputs::listenForConn},
		{"-send message", Inputs::sendMessage},
		{"-break connection", Inputs::breakConn},
		{"-quit", Inputs::quit}

	};
	
	EndToEnd et;
	
	std::string usr_input ="";
	std::getline(std::cin, usr_input);
	std::vector<std::string> tokens = input_tokenizer(usr_input);

	auto match = input_map.find(tokens[0]);

	if (match == input_map.end())
	{
		std::cout << "wrong input, try to type '-help' to see all possible inputs";
	}

	else
	{
		switch (match->second) 
		{
		case Inputs::help:
			std::cout << helpMap();

		case Inputs::makeConn:

			usr_make_connection(tokens[1], custom_converter(tokens[2]), et);

		case Inputs::listenForConn:
			usr_listen_connection(et);

		case Inputs::sendMessage:
			usr_send_message(tokens[1], et);

		case Inputs::breakConn:
			usr_break_connection(et);
		}
	}
	

}


int main()
{
	uint16_t port = 4000;
	 

//	 EndToEnd istance(port);
//	 istance.wait_for_connection();
//	 istance.make_connection("192.168.1.106", port);
//	 std::vector<uint8_t> expl_msg = { 'C','A','C','A'};
//	 //NetMessage msg(expl_msg, expl_msg);	
//	 //istance.send_message(&msg);
//	 istance.run_context();
//

	return 0;
}

