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

		/*
			Declares an event type to the register.
		*/
		template<class E>
		void declare() {
			// ensure that 'E' inherits from Event
			static_assert(std::is_base_of<Event, E>::value, 
				"EventRegister.declare<E>() can only take template types that inherit from ostf::Event.");

			// get the key of the event
			std::string key = E::id;

			// ensure there is no current generator with this id
			// this might mean that the same event has been declared twice
			// or it might mean that two events have been given the same id
			BaseEventGenerator* currentGenerator = _generators[key];
			if (currentGenerator != nullptr) {
				throw std::invalid_argument("The events id propert has already been declared");
			}

			// create the generator and pop it into the map
			_generators[key] = new EventGenerator<E>();
		}

		/*
			Attempts to create an event from a given id.
			If the id is not recognised or cannot be generated
			then nullptr will be returned.
		*/
		Event* createEvent(ostf::Buffer& buffer) {
			// get the base event generator using the id
			std::string id;
			buffer.read_string("id", id);
			BaseEventGenerator* generator = _generators[id];
		
			// ensure generator exists, if not - return nullptr
			if (generator == nullptr)
				return nullptr;

			// use the event generator to create the event
			return generator->generate(buffer);
		}
	};
}