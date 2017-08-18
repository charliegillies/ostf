#pragma once

#include "Event.h"
#include "EventRegister.h"
#include <string>

namespace ostf
{
	/*
		Utility for serializing events to and from strings.
	*/
	class EventSerializer
	{
	private:
		static EventRegister* _evRegister;

	public:
		/*
			Initializes the event serializer.
		*/
		static void init(EventRegister* reg);

		/*
			Writes an event from its object to string.
		*/
		static std::string serialize(Event* ev);

		/*
			Creates an event from a serialized event (string data).
		*/
		static Event* deserialize(std::string eventData);
	};
}