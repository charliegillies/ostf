#include "core/ostf.h"

#include "apps/App.h"
#include "apps/ClientApp.h"
#include "apps/ServerApp.h"

#include <iostream>

using namespace ostf;

int main(int argc, char* argv[])
{
	// ensure that we have one argument
	// keep in mind that the first argument passed is the program name
	if(argc != 2) {
		std::cout << "A command line argument of 'server' or 'client' is required. Program exiting." << '\n';
		return -1;
	}

	// get the second argument
	std::string appArg = argv[1];
	Application* app = nullptr;

	if(appArg == "server") {
		app = new ServerApp();
	}
	else if(appArg == "client") {
		app = new ClientApp();
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
