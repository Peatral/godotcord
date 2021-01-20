#ifndef GODOTCORD_H
#define GODOTCORD_H

#include <Godot.hpp>
#include <Object.hpp>
#include <Texture.hpp>
#include <String.hpp>
#include "discord-files/discord.h"
//#include "godotcord_activity.h"
//#include "godotcord_relationship.h"
//#include "godotcord_lobby.h"

//#include "godotcord_activity_manager.h"

using namespace godot;

class Godotcord : public Object {
    GODOT_CLASS(Godotcord, Object)

private:
	discord::Core *_core{};
	bool init_bool = false;
	String _route;

	void _init_discord();

public:
	void _init() { };
	static void _register_methods();

	static Godotcord *singleton;
	static Godotcord *get_singleton();

	static const int CreateFlags_DEFAULT = 0;
	static const int CreateFlags_NO_REQUIRE_DISCORD = 1;

    void init(discord::ClientId clientId, int createFlags);
	void init_debug(discord::ClientId clientId, String id, int createFlags);

	void run_callbacks();

	bool is_init() const {
		return init_bool;
	}

	String get_route() { return _route; }

	void removeRouteEvent();

	discord::Core *get_core();

    Godotcord();
	~Godotcord();
};

#endif
