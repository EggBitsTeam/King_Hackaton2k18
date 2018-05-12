#ifndef __j1COLLISION_H__
#define __j1COLLISION_H__

#include "ctModule.h"
#include "ctPoint.h"

#include "SDL\include\SDL_rect.h"

#include <list>
#include <vector>
#include <algorithm>
using namespace std;

enum ColliderType {

	ColliderType_NoType = -1,

	/// Player
	ColliderType_Player,

	/// Buildings
	ColliderType_Inem,
	ColliderType_Enterprise,
	ColliderType_XXX,
	ColliderType_Street,
	ColliderType_University,
	ColliderType_DiningRoom,

	/// Change between characters
	ColliderType_ChangeStreet,
	ColliderType_ChangeUniversity,
	ColliderType_ChangeDiningRoom,

	/// End
	ColliderType_End,

	ColliderType_MaxColliders
};

enum CollisionState {

	CollisionState_NoCollision,
	CollisionState_OnEnter,
	CollisionState_OnExit
};

struct Collider;

class j1Collision : public ctModule
{
public:

	j1Collision();
	~j1Collision();

	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();
	void DebugDraw();

	void HandleTriggers();

	// Colliders
	Collider* CreateCollider(ColliderType colliderType, SDL_Rect colliderRect, ctModule* callback);
	bool RemoveCollider(Collider* collider);

public:

	bool matrix[ColliderType_MaxColliders][ColliderType_MaxColliders];
	SDL_Color debugColors[ColliderType_MaxColliders];

private:

	list<Collider*> colliders;
};

// ---------------------------------------------------------------------
// Collider: struct representing a collider
// ---------------------------------------------------------------------

struct Collider
{
	Collider(SDL_Rect colliderRect, ColliderType colliderType, ctModule* callback);

	~Collider();

	// Position
	void SetPos(int x, int y);
	iPoint GetPos() const;

	// Collision
	bool CheckCollision(const SDL_Rect& r) const;

	// -----

	// Info
	SDL_Rect colliderRect = { 0,0,0,0 };
	ColliderType colliderType = ColliderType_NoType;
	ctModule* callback = nullptr;

	// Parameters
	bool isTrigger = true;
	bool isValid = true;
	bool isRemove = false;

	// Collision
	list<Collider*> collidingGroups;
	list<Collider*> lastCollidingGroups;
};

#endif //__j1COLLISION_H__