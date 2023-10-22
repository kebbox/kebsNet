#pragma once
#include "utils.h"



std::string utils::helpMap()
{
	std::string help = "Welcome to the help section!\n "
		" currently the app is under development \n"
		" try the following inputs: \n"
		" '>help' display this message\n"
		" '>make connection <ip, port>' \n"
		" '>send message <message>'\n"
		" '>listen for connection <port>'\n"
		" '>break connection'\n";
		" '>quit' end this program";
		" '>stop listening' stop listen for connection";
	return help;
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

