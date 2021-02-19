#ifndef GODOTCORD_UTILS_H
#define GODOTCORD_UTILS_H

#include <Godot.hpp>
#include <String.hpp>

#define ADD_GODOTCORD_PROPERTY_INT(class, property)            		\
	godot::register_property<class, int>(#property, &class ::##property, 0);

#define ADD_GODOTCORD_PROPERTY_STRING(class, property)            	\
	godot::register_property<class, String>(#property, &class ::##property, "");

#endif