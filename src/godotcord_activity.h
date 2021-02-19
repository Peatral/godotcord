#ifndef GODOTCORD_ACTIVITY_H
#define GODOTCORD_ACTIVITY_H

#include <Godot.hpp>
#include <Reference.hpp>
#include <String.hpp>
#include <Dictionary.hpp>
#include "godotcord_utils.h"
#include "discord-files/types.h"

using namespace godot;

class GodotcordActivity : public Reference {
	GODOT_CLASS(GodotcordActivity, Reference)

public:
	enum ActivityRequestReply {
		NO,
		YES,
		IGNORE
	};

	enum ActivityActionType {
		JOIN = 1,
		SPECTATE = 2
	};

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, state)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, details)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, large_image)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, large_text)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, small_image)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, small_text)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, party_id)
		ADD_GODOTCORD_PROPERTY_INT(GodotcordActivity, party_max)
		ADD_GODOTCORD_PROPERTY_INT(GodotcordActivity, party_current)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, match_secret)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, join_secret)
		ADD_GODOTCORD_PROPERTY_STRING(GodotcordActivity, spectate_secret)
		ADD_GODOTCORD_PROPERTY_INT(GodotcordActivity, start)
		ADD_GODOTCORD_PROPERTY_INT(GodotcordActivity, end)
		
		ADD_GODOTCORD_PROPERTY_INT(GodotcordActivity, application_id);

		/*BIND_ENUM_CONSTANT(NO);
		BIND_ENUM_CONSTANT(YES);
		BIND_ENUM_CONSTANT(IGNORE);

		BIND_ENUM_CONSTANT(JOIN);
		BIND_ENUM_CONSTANT(SPECTATE);*/
	}

public:
	static Dictionary from_discord_activity(discord::Activity p_act) {
		Dictionary ret;
		ret["state"] = p_act.GetState();
		ret["details"] = p_act.GetDetails();
		ret["party_id"] = p_act.GetParty().GetId();
		ret["party_current"] = p_act.GetParty().GetSize().GetCurrentSize();
		ret["party_max"] = p_act.GetParty().GetSize().GetMaxSize();
		ret["application_id"] = p_act.GetApplicationId();
		ret["match_secret"] = p_act.GetSecrets().GetMatch();
		ret["join_secret"] = p_act.GetSecrets().GetJoin();
		ret["spectate_secret"] = p_act.GetSecrets().GetSpectate();
		ret["start"] = p_act.GetTimestamps().GetStart();
		ret["end"] = p_act.GetTimestamps().GetEnd();

		return ret;
	}

	String state = "";
	String details = "";
	String large_image = "";
	String large_text = "";
	String small_image = "";
	String small_text = "";
	String party_id = "";
	int party_max = -1;
	int party_current = -1;
	String match_secret = "";
	String join_secret = "";
	String spectate_secret = "";
	int start = 0;
	int end = 0;

	int64_t application_id;
};

/*VARIANT_ENUM_CAST(GodotcordActivity::ActivityRequestReply);
VARIANT_ENUM_CAST(GodotcordActivity::ActivityActionType);*/

#endif
