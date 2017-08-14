#include "core/ostf.h"

#include "apps/App.h"
#include "apps/ClientApp.h"
#include "apps/ServerApp.h"

#include <iostream>
#include "czmq.h"

using namespace ostf;

int main(int argc, char* argv[])
{
	// ensure that we have one argument
	// keep in mind that the first argument passed is the program name
	if(argc != 3) {
		std::cout << "Command line arguments (client/server) and an ip address are required." << '\n';
		return -1;
	}

	// get the second arg (client/server) & third arg (bind address)
	std::string appArg 	= argv[1];
	std::string address = argv[2];
	Application* app	  = nullptr;

	address = "@tcp://" + address + ":5560";

	if(appArg == "server") {
		app = new ServerApp(address);
		std::cout << "Server application initialized: " << address << '\n';
	}
	else if(appArg == "client") {
		app = new ClientApp(address);
		std::cout << "Client application initialized: " << address << '\n';
	}
	else {
		std::cout << "Incorrect cmd arg: '" << appArg << "' was passed. Arg 'client' or 'server' was expected." << '\n';
		return -1;
	}

	// app is valid, start
	app->run();

	// display exit to terminal for debugging purposes
	std::cout << "OSTF demo program exit." << '\n';
	delete app;
	return 0;
}
