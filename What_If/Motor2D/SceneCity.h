#ifndef __SceneCity_H__
#define __SceneCity_H__

#include "ctModule.h"
#include "Entity.h"

#include <string>
#include <vector>

class Goal_Think;
class Homeless;
class Black;
class White;
class Girl;

class UIImage;
class UILabel;

class SceneCity : public ctModule
{

public:

	SceneCity();

	// Destructor
	virtual ~SceneCity();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnUITrigger(UIElement* elementTriggered, UI_State ui_state);

	void OnCollision(Collider* c1, Collider* c2, CollisionState collisionState);

public:
	// Player
	Homeless* homelessEntity = nullptr;
	Girl* girlEntity = nullptr;
	Black* blackEntity = nullptr;
	White* whiteEntity = nullptr;

	enum Current_Player
	{
		NO_FOLLOW,
		WHITE_ACTUAL,
		BLACK_ACTUAL,
		HOMELESS_ACTUAL,
		GIRL_ACTUAL,
	} currentPlayer = NO_FOLLOW;

private:

	Goal_Think* homelessBrain = nullptr;
	Goal_Think* girlBrain = nullptr;
	Goal_Think* blackBrain = nullptr;
	Goal_Think* whiteBrain = nullptr;

	// Map
	SDL_Texture* mapTexture = nullptr;

	// Debug
	bool isDebugCollision = false;

	// UI
	UIImage* title = nullptr;
	UILabel* pressStart = nullptr;
};


#endif // __SceneCity_H__
