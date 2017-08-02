#include "core/Event.h"
#include "core/EventRegister.h"
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
	Event* parsed = reg.generate(buffer);
	// ensure the event was parsed properly
	assert(parsed != nullptr);

	return parsed;
}

int main()
{
	// create an event register, declare our events
	EventRegister evRegister;
	evRegister.declare<CreateLobbyEvent>();

	// create a lobby event, convert it to a json string
	CreateLobbyEvent createLobbyEvent;
	std::string j = eventToString(createLobbyEvent);

	// debug print the json string
	std::cout << j << std::endl;

	// reform the event from the json string
	Event* e = eventFromString(j, evRegister);
	CreateLobbyEvent* parsedLobbyEvent = (CreateLobbyEvent*)e;

	system("pause");

	delete parsedLobbyEvent;
	return 0;
}