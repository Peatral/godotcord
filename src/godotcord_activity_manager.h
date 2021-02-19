#ifndef GODOTCORD_ACTIVITY_MANAGER_H
#define GODOTCORD_ACTIVITY_MANAGER_H

#include <Godot.hpp>
#include <Object.hpp>
#include <String.hpp>

#include "godotcord_activity.h"

using namespace godot;

class GodotcordActivityManager : public Object {
	GODOT_CLASS(GodotcordActivityManager, Object);

public:
	void _init() { };
	static void _register_methods();

	void init();

	void set_activity(Ref<GodotcordActivity> p_activity);
	void clear_activity();

	void send_request_reply(int64_t p_user_id, GodotcordActivity::ActivityRequestReply p_reply);
	void send_invite(int64_t p_user_id, GodotcordActivity::ActivityActionType p_type, String p_message);
	void accept_invite(int64_t p_user_id);

	GodotcordActivityManager();
	~GodotcordActivityManager();
};

#endif //GODOTCORD_ACTIVITY_MANAGER_H
