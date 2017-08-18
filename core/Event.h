#pragma once

#include "Buffer.h"

namespace ostf
{
	/*
		Base class for a event.
		Events are the main form of communication across the network.
	*/
	class Event
	{
	public:
		Event() { }

		virtual ~Event() = default;

		/*
			Writes the event data.
		*/
		virtual void write(Buffer& out) = 0;

		/*
			Reads the event data.
		*/
		virtual void read(Buffer& in) = 0;

		/*
			Gets the id of the event.
		*/
		virtual std::string getId() = 0;
	};
}