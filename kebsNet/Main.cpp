
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "net_common.h"
#include "NetMessage.h"
#include "EndToEnd.h"
#include "Core.h"



int main()
{
	std::cout << "Welcome to the kebsNet type somthing to start:" << std::endl;
	// main loop
	// right now i will use a duble loop , wich is ugly , until i get a better idea
	user_input();

	return 0;
}

