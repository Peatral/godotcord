#include "godotcord_activity_manager.h"
#include "godotcord.h"
#include <Dictionary.hpp>

void GodotcordActivityManager::_register_methods() {
	register_method("set_activity", &GodotcordActivityManager::set_activity);
	register_method("clear_activity", &GodotcordActivityManager::clear_activity);
	register_method("send_request_reply", &GodotcordActivityManager::send_request_reply);
	register_method("send_invite", &GodotcordActivityManager::send_invite);
	register_method("accept_invite", &GodotcordActivityManager::accept_invite);

	register_signal("activity_join_request", "name", "id");
	register_signal("activity_invite", "type", "name", "id", "activity");
	register_signal("activity_join", "secret");
	register_signal("activity_spectate", "secret");
}

void GodotcordActivityManager::set_activity(Ref<GodotcordActivity> p_activity) {
	discord::Activity activity{};

	if (p_activity->state != "") {
		activity.SetState(p_activity->state.utf8().get_data());
	}

	if (p_activity->details != "") {
		activity.SetDetails(p_activity->details.utf8().get_data());
	}

	if (p_activity->large_text != "") {
		activity.GetAssets().SetLargeText(p_activity->large_text.utf8().get_data());
	}

	if (p_activity->large_image != "") {
		activity.GetAssets().SetLargeImage(p_activity->large_image.utf8().get_data());
	}

	if (p_activity->small_text != "") {
		activity.GetAssets().SetSmallText(p_activity->small_text.utf8().get_data());
	}

	if (p_activity->small_image != "") {
		activity.GetAssets().SetSmallImage(p_activity->small_image.utf8().get_data());
	}

	if (p_activity->party_id != "") {
		activity.GetParty().SetId(p_activity->party_id.utf8().get_data());
	}

	if (p_activity->party_max >= 0) {
		activity.GetParty().GetSize().SetMaxSize(p_activity->party_max);
	}

	if (p_activity->party_current >= 0) {
		activity.GetParty().GetSize().SetCurrentSize(p_activity->party_current);
	}

	if (p_activity->match_secret != "") {
		activity.GetSecrets().SetMatch(p_activity->match_secret.utf8().get_data());
	}

	if (p_activity->join_secret != "") {
		activity.GetSecrets().SetJoin(p_activity->join_secret.utf8().get_data());
	}

	if (p_activity->spectate_secret != "") {
		activity.GetSecrets().SetSpectate(p_activity->spectate_secret.utf8().get_data());
	}

	if (p_activity->start != 0) {
		activity.GetTimestamps().SetStart(p_activity->start);
	}

	if (p_activity->end != 0) {
		activity.GetTimestamps().SetEnd(p_activity->end);
	}

	Godotcord::get_singleton()->get_core()->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while settings the activity");
	});
}

void GodotcordActivityManager::clear_activity() {
	Godotcord::get_singleton()->get_core()->ActivityManager().ClearActivity([](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while clearing the activity");
	});
}

void GodotcordActivityManager::send_request_reply(int64_t p_user_id, GodotcordActivity::ActivityRequestReply p_reply) {
	Godotcord::get_singleton()->get_core()->ActivityManager().SendRequestReply(p_user_id, (discord::ActivityJoinRequestReply)p_reply, [this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Seomthing went wrong while replying to the request");
	});
}

void GodotcordActivityManager::send_invite(int64_t p_user_id, GodotcordActivity::ActivityActionType p_type, String p_message) {
	Godotcord::get_singleton()->get_core()->ActivityManager().SendInvite(p_user_id, (discord::ActivityActionType)p_type, p_message.utf8(), [this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Seomthing went wrong while sending the invite");
	});
}

void GodotcordActivityManager::accept_invite(int64_t p_user_id) {
	Godotcord::get_singleton()->get_core()->ActivityManager().AcceptInvite(p_user_id, [this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Seomthing went wrong while accepting the invite");
	});
}

void GodotcordActivityManager::init() {
	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivityInvite.Connect([this](discord::ActivityActionType p_type, discord::User p_user, discord::Activity p_activity) {
		emit_signal("activity_invite", (GodotcordActivity::ActivityActionType)p_type, p_user.GetUsername(), p_user.GetId(), GodotcordActivity::from_discord_activity(p_activity));
	});

	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivityJoin.Connect([this](const char *secret) {
		emit_signal("activity_join", secret);
	});

	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivityJoinRequest.Connect([this](discord::User p_user) {
		emit_signal("activity_join_request", p_user.GetUsername(), p_user.GetId());
	});

	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivitySpectate.Connect([this](const char *secret) {
		emit_signal("activity_spectate", secret);
	});
}

GodotcordActivityManager::GodotcordActivityManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordActivityManager should exist")
}

GodotcordActivityManager::~GodotcordActivityManager() {

}
