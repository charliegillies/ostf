#include "CreateLobbyEvent.h"

const std::string ostf::CreateLobbyEvent::id = "CREATE_LOBBY";

ostf::CreateLobbyEvent::CreateLobbyEvent()
{
	// default lobby settings
	lobbySettings.maxPlayers = 2;
	lobbySettings.name = "Default Lobby";
	lobbySettings.password = "";
}

void ostf::CreateLobbyEvent::write(ostf::Buffer & out)
{
	std::string nid = id;
	out.write_string("id", nid);

	Buffer& settings = out.create_child("settings");
	settings.write_int("maxPlayers", lobbySettings.maxPlayers);
	settings.write_string("name", lobbySettings.name);
	settings.write_string("password", lobbySettings.password);
}

void ostf::CreateLobbyEvent::read(ostf::Buffer & in)
{

}
