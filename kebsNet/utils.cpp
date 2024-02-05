#pragma once
#include "utils.h"



std::string utils::helpMap()
{
	std::string help = "Welcome to the help section!\n "
		" currently the app is under development \n"
		" try the following inputs: \n"
		" '>help' display this message\n"
		" '>make connection <ip, port>' \n"
		" '>send message <\"message\">'\n"
		" '>listen for connection <port>'\n"
		" '>break connection'\n";
		" '>quit' end this program\n";
		" '>stop listening' stop listen for connection\n";
	return help;
}

bool utils::is_message_complete(const std::vector<char>& messageBuffer) {
	// Check if the termination character is present in the messageBuffer
	for (char ch : messageBuffer) {
		if (ch == '\0') {
			return true;  // Message is complete
		}
	}
	return false;  // Termination character not found
}
	


uint16_t utils::custom_converter(std::string input)
{
	//hardcoding conversion for string input
	//adding a check for invalid input
	std::string numbers = "1234567890";

	if (input.back() == ' ') {
		input.pop_back();

	}
	for (auto i : input) {
		if (numbers.find(i) == std::string::npos) {
			std::cout << "error invalid port!" << std::endl;
			return 0;
		} 
	}
	int partial = stoi(input);
	return static_cast<uint16_t>(partial);

}

std::string utils::ignore_spaces(std::string name) {
	if (name.find(' ')) {

		name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
		return name;
	}
}
std::string utils::message_converter(std::string message)
	{
	char standard_quote = '\"';
	
	char first = message[0];
	//here message.front give me the ref of the first element this could be a problem with async operations
	//will see how it goes
	if (message.back() == standard_quote && first == standard_quote) {
		//message looks valid
		message.erase(std::remove(message.begin(), message.end(), '"'), message.end());
		return message;
	}

	else {
		return "@#$%%575339"; // for now will return a very specific string as a non valid input, i know is bad
	}
	
	
	}
