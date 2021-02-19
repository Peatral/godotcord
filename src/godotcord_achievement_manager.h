#ifndef GODOTCORD_ACHIEVEMENT_MANAGER
#define GODOTCORD_ACHIEVEMENT_MANAGER

#include <Godot.hpp>
#include <Object.hpp>
#include <String.hpp>

using namespace godot;

class GodotcordAchievementManager : public Object {
	GODOT_CLASS(GodotcordAchievementManager, Object)

public:
	void _init() { };
	static void _register_methods();

	void set_user_achievement(int64_t p_achievement_id, int8_t p_percent);
	void fetch_user_achievements(Object *p_object, StringName p_funcname);
	Array get_user_achievements();


	void init();
	GodotcordAchievementManager();
};


#endif //GODOTCORD_ACHIEVEMENT_MANAGER
