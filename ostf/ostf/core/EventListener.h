#pragma once

#include "Event.h"
#include <map>
#include <cassert>
#include <functional>

namespace ostf
{
	/*
		
	*/
	class EventListener
	{
	private:
		class IBaseListener {
		public:
			virtual void onEventRecv(Event* e) = 0;
		};
		
		template<class E>
		class EListener : public IBaseListener {
		private:
			std::function<void(E*)> _f;
 
		public:
			EListener(std::function<void(E*)> f) : _f(f) { }

			virtual void onEventRecv(Event* e) override {
				E* event = static_cast<E*>(e);
				_f(event);
			}
		};

	private:
		std::map<std::string, IBaseListener*> _listeners;

	public:
		EventListener() { }

		~EventListener() {
			for (auto v : _listeners)
				delete v.second;
		}

		void onEventRecv(Event* e) {
			// get listener, if null - don't invoke
			IBaseListener* listener = _listeners[e->getId()];
			if (listener == nullptr) return;

			// otherwise, invoke
			listener->onEventRecv(e);
		}

		template<class E>
		void listen(std::function<void (E*)> f) {
			if (f == NULL) {
				throw std::invalid_argument("EventListener.listen() std::function param cannot be null.");
			}

			std::string key = E::id;

			// check if we have a listener already 
			// ensure that we don't..
			assert(_listeners[key] == nullptr);

			// create a listener, put it into the map
			EListener<E>* listener = new EListener<E>(f);
			_listeners[key] = listener;
		}
	};
}