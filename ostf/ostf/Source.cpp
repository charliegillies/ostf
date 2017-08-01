#include "core/Event.h"
#include "core/EventRegister.h"
#include "core/Buffer.h"
#include "core/JsonBuffer.h"

#include "events/CreateLobbyEvent.h"

#include <iostream>

using namespace ostf;

int main()
{
	// create an event register, declare our events
	EventRegister evRegister;
	evRegister.declare<CreateLobbyEvent>();

	// create a json buffer, try write an event
	nlohmann::json json;
	JsonBuffer jsonBuffer{ json };
	
	CreateLobbyEvent createLobbyE;
	createLobbyE.write(jsonBuffer);

	std::string j = json.dump(4);
	std::cout << j << std::endl;

	system("pause");
	return 0;
}