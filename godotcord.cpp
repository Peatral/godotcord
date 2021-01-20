#include "godotcord.h"
/*#include "godotcord_achievement_manager.h"
#include "godotcord_relationship_manager.h"
#include "godotcord_store_manager.h"
#include "godotcord_user_manager.h"
#include "core/func_ref.h"*/

Godotcord *Godotcord::singleton = NULL;

Godotcord::Godotcord() {
	_route = String("");

	singleton = this;
}

Godotcord::~Godotcord() {
	if (this == singleton && this->is_init()) {
		_core->~Core();
	}
}

Godotcord* Godotcord::get_singleton() {
	return singleton;
}

void Godotcord::run_callbacks() {
	if (init_bool) {
		_core->RunCallbacks();
	}
}

void Godotcord::_register_methods() {
    register_method("init", &Godotcord::init);
	register_method("init_debug", &Godotcord::init_debug);
	register_method("run_callbacks", &Godotcord::run_callbacks);

	//register_property("CreateFlags_DEFAULT", Godotcord::CreateFlags_DEFAULT, Godotcord::CreateFlags_DEFAULT);
	//register_property("CreateFlags_NO_REQUIRE_DISCORD", Godotcord::CreateFlags_NO_REQUIRE_DISCORD, Godotcord::CreateFlags_NO_REQUIRE_DISCORD);

}
	
void Godotcord::init(discord::ClientId clientId, int createFlags = Godotcord::CreateFlags_DEFAULT) {
	discord::Result result = discord::Core::Create(clientId, createFlags, &_core);

	//ERR_FAIL_COND_V(result != discord::Result::Ok, ERR_CANT_CONNECT);

	_init_discord();
}

void Godotcord::init_debug(discord::ClientId clientId, String id, int createFlags = Godotcord::CreateFlags_DEFAULT) {
#ifdef _WIN32
	_putenv_s("DISCORD_INSTANCE_ID", id.utf8().get_data());
#else
	setenv("DISCORD_INSTANCE_ID", id.utf8(), true);
#endif
	discord::Result result = discord::Core::Create(clientId, createFlags, &_core);

    //ERR_FAIL_COND(result != discord::Result::Ok);

	_init_discord();
}

void Godotcord::_init_discord() {
	init_bool = true;

	_core->SetLogHook(discord::LogLevel::Info, [](discord::LogLevel level, const char *msg) {
		switch (level) {
			case discord::LogLevel::Warn:
				Godot::print("[DiscordGameSDK][Warn]");
				break;
			case discord::LogLevel::Info:
				Godot::print("[DiscordGameSDK][Info]");
				break;
			case discord::LogLevel::Error:
				Godot::print("[DiscordGameSDK][ERR]");
				break;
		}
	});

	_core->NetworkManager().OnRouteUpdate.Connect([this](const char *p_route) {
		_route = String(p_route);
	});

	/*GodotcordAchievementManager::get_singleton()->init();
	GodotcordActivityManager::get_singleton()->init();
	GodotcordRelationshipManager::get_singleton()->init();
	GodotcordStoreManager::get_singleton()->init();
	GodotcordUserManager::get_singleton()->init();*/
}

void Godotcord::removeRouteEvent() {
	_core->NetworkManager().OnRouteUpdate.DisconnectAll();
}

discord::Core* Godotcord::get_core() {
	return _core;
}
