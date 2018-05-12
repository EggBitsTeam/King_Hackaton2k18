#ifndef __SceneCity_H__
#define __SceneCity_H__

#include "ctModule.h"
#include "Entity.h"

#include <string>
#include <vector>

class Player;
class Goal_Think;

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

private:

	// Player
	Player* player = nullptr;
	Goal_Think* brain = nullptr;

	// Map
	SDL_Texture* mapTexture = nullptr;

	// Debug
	bool isDebugCollision = false;

};


#endif // __SceneCity_H__
