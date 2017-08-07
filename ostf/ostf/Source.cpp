#include "core/Event.h"
#include "core/EventSerializer.h"
#include "core/EventRegister.h"
#include "core/EventListener.h"
#include "core/Buffer.h"
#include "core/JsonBuffer.h"

#include "events/CreateLobbyEvent.h"

#include <iostream>

using namespace ostf;

void onCreateLobbyEvent(CreateLobbyEvent* e) {
	std::cout << "onCreateLobbyEvent()" << std::endl;
}

struct LobbyCreatedExample {
	void onLobbyCreated(CreateLobbyEvent* e) {
		std::cout << "LobbyCreatedExample.onLobbyCreated()" << std::endl;
	}
};

int main()
{
	// create an event register, declare our events
	EventRegister evRegister;
	evRegister.declare<CreateLobbyEvent>();

	// Initialize the event serializer with our event register
	EventSerializer::init(&evRegister);

	// create a listener, start listening
	EventListener evListener;
	std::function<void(CreateLobbyEvent*)> callback;

	// Lambda function
//	callback = [](CreateLobbyEvent* e) {
//		std::cout << "Lambda invoked" << std::endl;
//	};

	// Global/Free function
//	callback = onCreateLobbyEvent;

	// Member function
	LobbyCreatedExample ex;
	callback = std::bind(&LobbyCreatedExample::onLobbyCreated, &ex, std::placeholders::_1);

	// begin listening
	evListener.listen<CreateLobbyEvent>(callback);

	// create a lobby event, convert it to a json string
	CreateLobbyEvent createLobbyEvent;
	std::string data = EventSerializer::serialize(&createLobbyEvent);

	// debug print the json string
	std::cout << data << std::endl;

	// reform the event from the json string
	Event* e = EventSerializer::deserialize(data);

	// inform the listener that we've got an event
	evListener.onEventRecv(e);

	delete e;
	return 0;
}
