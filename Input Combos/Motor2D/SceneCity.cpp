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
#include "Player.h"
#include "Goal.h"
#include "ctRender.h"
#include "j1Printer.h"
#include "Homeless.h"
#include "Black.h"
#include "White.h"
#include "Girl.h"
#include "UIImage.h"
#include "UILabel.h"

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

	int scale = App->win->GetScale();
	uint width, height;
	App->win->GetWindowSize(width, height);

	// UI
	title = (UIImage*)App->gui->AddUIImage(120, 50, { 80,1,103,31 });
	pressStart = (UILabel*)App->gui->AddUILabel(130, 150, "Press A to start", ColorWhite, 12);

	// Map
	mapTexture = App->tex->Load("textures/map.png");
	mapWidth = 4194;
	mapHeight = 316;

	// Colliders
	SDL_Rect inemRect = { 280,184,160,107 };
	App->collision->CreateCollider(ColliderType_Inem, inemRect, this);

	SDL_Rect enterpriseRect = { 768,151,242,140 };
	App->collision->CreateCollider(ColliderType_Enterprise, enterpriseRect, this);

	SDL_Rect xxxRect = { 1380,183,159,107 };
	App->collision->CreateCollider(ColliderType_XXX, xxxRect, this);

	SDL_Rect streetRect = { 1539,151,273,139 };
	App->collision->CreateCollider(ColliderType_Street, streetRect, this);

	SDL_Rect universityRect = { 2740,151,448,143 };
	App->collision->CreateCollider(ColliderType_University, universityRect, this);

	SDL_Rect diningRoomRect = { 3706,190,160,107 };
	App->collision->CreateCollider(ColliderType_DiningRoom, diningRoomRect, this);

	SDL_Rect changeStreetRect = { 1485,183,55,107 };
	App->collision->CreateCollider(ColliderType_ChangeStreet, changeStreetRect, this);

	SDL_Rect changeUniversityRect = { 2468,151,272,143 };
	App->collision->CreateCollider(ColliderType_ChangeUniversity, changeUniversityRect, this);

	SDL_Rect changeDiningRoomRect = { 3520,151,186,146 };
	App->collision->CreateCollider(ColliderType_ChangeDiningRoom, changeDiningRoomRect, this);

	SDL_Rect endRect = { 3941,151,253,147 };
	App->collision->CreateCollider(ColliderType_End, endRect, this);

	whiteEntity = (White*)App->entities->SpawnEntity(270, 260, EntityType::WHITE);
	girlEntity = (Girl*)App->entities->SpawnEntity(200, 260, EntityType::GIRL);
	blackEntity = (Black*)App->entities->SpawnEntity(120, 260, EntityType::BLACK);
	homelessEntity = (Homeless*)App->entities->SpawnEntity(60, 260, EntityType::HOMELESS);
/*
	whiteEntity = (White*)App->entities->SpawnEntity(-270, 260, EntityType::WHITE);
	girlEntity = (Girl*)App->entities->SpawnEntity(-200, 260, EntityType::GIRL);
	blackEntity = (Black*)App->entities->SpawnEntity(-120, 260, EntityType::BLACK);
	homelessEntity = (Homeless*)App->entities->SpawnEntity(60, 260, EntityType::HOMELESS);
*/
	// Player's brain
	blackBrain = new Goal_Think(blackEntity);
	blackBrain->RemoveAllSubgoals();
	whiteBrain = new Goal_Think(whiteEntity);
	whiteBrain->RemoveAllSubgoals();
	homelessBrain = new Goal_Think(homelessEntity);
	homelessBrain->RemoveAllSubgoals();
	girlBrain = new Goal_Think(girlEntity);
	girlBrain->RemoveAllSubgoals();

	// Intro cinematic
	//
	blackBrain->AddGoal_IntroCinematic(title, pressStart);

	currentPlayer = NO_FOLLOW;

	homelessEntity->StopPlayer(true);
	girlEntity->StopPlayer(true);
	whiteEntity->StopPlayer(true);
	blackEntity->StopPlayer(true);

	App->win->GetWindowSize(width, height);

	barHeight = 150;

	// Black bars
	App->gui->AddUIImage( 0, -120, { 99, 96, 680, 150 }, this);
	App->gui->AddUIImage(0, App->render->camera.h - (barHeight * App->win->GetScale()) + 100, { 99, 96, 680, 150 }, this);

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
	int scale = App->win->GetScale();

	// Update brains
	blackBrain->ProcessSubgoals(dt);
	whiteBrain->ProcessSubgoals(dt);
	homelessBrain->ProcessSubgoals(dt);
	girlBrain->ProcessSubgoals(dt);

	// Blit map
	App->printer->PrintSprite({ 0,0 }, mapTexture, { 0,0,mapWidth, mapHeight }, Layers_Map);

	// Debug camera
	float cameraSpeed = 1000.0f;
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += cameraSpeed * dt;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= cameraSpeed * dt;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += cameraSpeed * dt;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= cameraSpeed * dt;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && currentPlayer != HOMELESS_ACTUAL)
	{
		if (currentPlayer == GIRL_ACTUAL)
			girlEntity->EnterScene(false);
		else if (currentPlayer == BLACK_ACTUAL)
			blackEntity->EnterScene(false);
		else if (currentPlayer == WHITE_ACTUAL)
			whiteEntity->EnterScene(false);

		homelessEntity->EnterScene(true);
		currentPlayer = NO_FOLLOW;
		nextPlayer = Current_Player::HOMELESS_ACTUAL;
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && currentPlayer != GIRL_ACTUAL)
	{
		if (currentPlayer == HOMELESS_ACTUAL)
			homelessEntity->EnterScene(false);
		else if (currentPlayer == BLACK_ACTUAL)
			blackEntity->EnterScene(false);
		else if (currentPlayer == WHITE_ACTUAL)
			whiteEntity->EnterScene(false);

		girlEntity->EnterScene(true);
		currentPlayer = NO_FOLLOW;
		nextPlayer = Current_Player::GIRL_ACTUAL;
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && currentPlayer != WHITE_ACTUAL)
	{
		if (currentPlayer == GIRL_ACTUAL)
			girlEntity->EnterScene(false);
		else if (currentPlayer == BLACK_ACTUAL)
			blackEntity->EnterScene(false);
		else if (currentPlayer == HOMELESS_ACTUAL)
			homelessEntity->EnterScene(false);

		whiteEntity->EnterScene(true);
		currentPlayer = NO_FOLLOW;
		nextPlayer = Current_Player::WHITE_ACTUAL;
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN && currentPlayer != BLACK_ACTUAL)
	{
		if (currentPlayer == GIRL_ACTUAL)
			girlEntity->EnterScene(false);
		else if (currentPlayer == HOMELESS_ACTUAL)
			homelessEntity->EnterScene(false);
		else if (currentPlayer == WHITE_ACTUAL)
			whiteEntity->EnterScene(false);

		blackEntity->EnterScene(true);
		currentPlayer = NO_FOLLOW;
		nextPlayer = Current_Player::BLACK_ACTUAL;
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		currentPlayer = Current_Player::NO_FOLLOW;
		homelessEntity->StopPlayer(true);
		girlEntity->StopPlayer(true);
		whiteEntity->StopPlayer(true);
		blackEntity->StopPlayer(true);
	}

	// Debug draw
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		isDebugCollision = !isDebugCollision;

	if (isDebugCollision)
		App->collision->DebugDraw();

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

	App->tex->UnLoad(mapTexture);

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

		case ColliderType_Street:

			break;

		case ColliderType_University:

			break;

		case ColliderType_DiningRoom:

			break;

		case ColliderType_ChangeStreet:

			break;

		case ColliderType_ChangeUniversity:

			break;

		case ColliderType_ChangeDiningRoom:

			break;

		case ColliderType_End:

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
