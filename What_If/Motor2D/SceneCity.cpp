#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctAudio.h"
#include "ctWindow.h"
#include "ctEntities.h"
#include "ctFadeToBlack.h"
#include "ctGui.h"
#include "UIElement.h"

#include "SceneCity.h"


//randomize libs
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



SceneCity::SceneCity() : ctModule()
{
	name = "scene_city";
}

// Destructor
SceneCity::~SceneCity()
{}

// Called before render is available

bool SceneCity::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene City");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool SceneCity::Start()
{
	bool ret = true;

	App->entities->SpawnEntity(0, 0, EntityType::PLAYER);

	return ret;
}

// Called each loop iteration
bool SceneCity::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneCity::Update(float dt)
{
	

	return true;
}

// Called each loop iteration
bool SceneCity::PostUpdate()
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;


	return ret;
}

// Called before quitting
bool SceneCity::CleanUp()
{
	LOG("Freeing SceneCity");


	return true;
}

void SceneCity::OnUITrigger(UIElement* elementTriggered, UI_State ui_state)
{

}

