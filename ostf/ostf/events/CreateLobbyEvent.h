#pragma once

#include "../core/Event.h"

namespace ostf
{
	struct LobbySettings
	{
	public:
		std::string name;
		std::string password;
		int maxPlayers;
	};

	/*
		
	*/
	class CreateLobbyEvent : public Event
	{
	public:
		const static std::string id;

		LobbySettings lobbySettings;

		CreateLobbyEvent();
		
		// Inherited via Event
		virtual void write(Buffer & out) override;
		virtual void read(Buffer & in) override;
	};
}