#pragma once

#include <type_traits> // allows std::is_base_of<X,Y>
#include <map>

#include "Event.h"

namespace ostf
{
	/*
		The event register is a base class that simply holds
		a map of event ids to event generators. This means when
		we get a packet, we see what event id we have and from
		there we can generate that event without the need of a 
		large unmaintainable set of if statements.
	*/
	class EventRegister
	{
	private:
		class BaseEventGenerator {
		public:
			virtual Event* generate(Buffer& buffer) = 0;
		};

		template<class E>
		class EventGenerator : public BaseEventGenerator {
		public:
			// Inherited via BaseEventGenerator
			virtual Event* generate(Buffer & buffer) override
			{
				E* ev = new E();
				ev->read(buffer);
				return ev;
			}
		};

	private:
		std::map<std::string, BaseEventGenerator*> _generators;

	public:
		EventRegister() { }

		~EventRegister() {
			// delete everything in the _generators map
			for(auto pair : _generators) {
				delete pair.second;
			}
		}

		template<class E>
		void declare() {
			// ensure that 'E' inherits from Event
			static_assert(std::is_base_of<Event, E>::value, 
				"EventRegister.declare<E>() can only take template types that inherit from ostf::Event.");

			// create the generator and pop it into the map
			//EventGenerator<E>* generator = new EventGenerator<E>();

		}
	};
}