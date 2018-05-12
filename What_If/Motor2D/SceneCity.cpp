#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctAudio.h"
#include "ctWindow.h"
#include "ctEntities.h"
#include "ctFadeToBlack.h"
#include "ctGui.h"
#include "j1Collision.h"
#include "Goal.h"

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

	// Colliders
	SDL_Rect inemRect = { 0,0,0,0 };
	App->collision->CreateCollider(ColliderType_Barrio, inemRect, this);
	SDL_Rect enterpriseRect = { 0,0,0,0 };
	App->collision->CreateCollider(ColliderType_Barrio, enterpriseRect, this);
	SDL_Rect xxxRect = { 0,0,0,0 };
	App->collision->CreateCollider(ColliderType_Barrio, xxxRect, this);
	SDL_Rect barrioRect = { 0,0,0,0 };
	App->collision->CreateCollider(ColliderType_Barrio, barrioRect, this);
	SDL_Rect universityRect = { 0,0,0,0 };
	App->collision->CreateCollider(ColliderType_Barrio, universityRect, this);
	SDL_Rect diningRoomRect = { 0,0,0,0 };
	App->collision->CreateCollider(ColliderType_Barrio, diningRoomRect, this);

	return ret;
}

// Called before the first frame
bool SceneCity::Start()
{
	bool ret = true;

	//brain = new Goal_Think();

	//brain->RemoveAllSubgoals();
	//brain->AddGoal_WalkingIntro();

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

void SceneCity::OnCollision(Collider* c1, Collider* c2, CollisionState collisionState)
{
	// c1 is always ColliderType_Player

	switch (collisionState) {
	
	case CollisionState_OnEnter:

		switch (c2->colliderType) {
		
		case ColliderType_Inem:

			break;
		case ColliderType_Enterprise:

			break;
		case ColliderType_XXX:

			break;
		case ColliderType_Barrio:

			break;
		case ColliderType_University:

			break;
		case ColliderType_DiningRoom:

			break;
		default:
			break;
		}

		break;
	case CollisionState_OnExit:
		break;
	
	default:
		break;
	}
}
