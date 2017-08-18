#pragma once

#include <string>

namespace ostf
{
	/*
		Peers are the base class for network messages.
	*/
	class Peer
	{
	public:
		Peer();

		/*
		*
		*/
		virtual void setup();
	};
}
