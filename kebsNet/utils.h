#pragma once
#include "net_common.h"
namespace utils
{
	std::string helpMap();

	std::string ignore_spaces(std::string name);

	uint16_t custom_converter(std::string input);

	std::string message_converter(std::string message);

	bool is_message_complete(const std::vector<char>& messageBuffer);


}