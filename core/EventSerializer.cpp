#include "EventSerializer.h"
#include "json.hpp"
#include "JsonBuffer.h"
#include <cassert>

ostf::EventRegister* ostf::EventSerializer::_evRegister = nullptr;

void ostf::EventSerializer::init(EventRegister* reg)
{
	_evRegister = reg;
}

std::string ostf::EventSerializer::serialize(Event* ev)
{
	if (_evRegister == nullptr)
		throw std::invalid_argument("EventSerializer.init() must be called before serialize()");

	// write the event into json
	nlohmann::json jsonObj = nlohmann::json::object();
	ostf::JsonBuffer buffer{ jsonObj };

	ev->write(buffer);
	return jsonObj.dump(4);
}

ostf::Event* ostf::EventSerializer::deserialize(std::string eventData)
{
	if (_evRegister == nullptr)
		throw std::invalid_argument("EventSerializer.init() must be called before deserialize()");

	// write string to json object, write that jObj to the buffer
	nlohmann::json jsonObj = nlohmann::json::parse(eventData);
	ostf::JsonBuffer buffer{ jsonObj };

	// create an event from the string
	Event* e = _evRegister->createEvent(buffer);
	assert(e != nullptr);

	return e;
}
