#include "core/Event.h"
#include "core/EventRegister.h"
#include "core/EventListener.h"
#include "core/Buffer.h"
#include "core/JsonBuffer.h"

#include "events/CreateLobbyEvent.h"

#include <iostream>

using namespace ostf;

std::string eventToString(Event& e)
{
	nlohmann::json json;
	JsonBuffer buffer{ json };

	e.write(buffer);
	return json.dump(4);
}

Event* eventFromString(std::string v, EventRegister& reg)
{
	// parse string to a json object, create buffer
	nlohmann::json json = nlohmann::json::parse(v);
	JsonBuffer buffer{ json };

	// use the event register to parse the event
	Event* parsed = reg.createEvent(buffer);
	// ensure the event was parsed properly
	assert(parsed != nullptr);

	return parsed;
}

int main()
{
	// create an event register, declare our events
	EventRegister evRegister;
	evRegister.declare<CreateLobbyEvent>();

	EventListener evListener;
	evListener.listen<CreateLobbyEvent>([] (CreateLobbyEvent* e) {
		std::cout << "Create Lobby Event Recv'd" << std::endl;
	});

	// create a lobby event, convert it to a json string
	CreateLobbyEvent createLobbyEvent;
	std::string j = eventToString(createLobbyEvent);

	// debug print the json string
	std::cout << j << std::endl;

	// reform the event from the json string
	Event* e = eventFromString(j, evRegister);
	
	// inform the listener that we've got an event
	evListener.onEventRecv(e);

	system("pause");

	delete e;
	return 0;
}