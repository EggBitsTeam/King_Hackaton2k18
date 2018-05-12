#include "ctDefs.h"
#include "ctLog.h"
#include "Dialogs.h"

#include "ctInput.h"
#include "ctApp.h"
#include "ctTextures.h"

#include "SDL/include/SDL.h"

Dialogs::Dialogs() : ctModule()
{
	name = "dialogs";
}

// Destructor
Dialogs::~Dialogs()
{}


// Called before render is available
bool Dialogs::Awake(pugi::xml_node& config)
{
	LOG("Loading Dialogs");
	bool ret = true;
	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadDialogs(config_file);

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations && ret; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "tom_01")
			LoadAnimation(animations, &tom_01);


	}
	return ret;
}

bool Dialogs::Start()
{
	atlas = App->tex->Load("dialogs/atlas.png");

	return true;
}


// Called before quitting
bool Dialogs::CleanUp()
{
	if (!active)
		return true;

	return true;
}

void Dialogs::LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
}