#include "ctDefs.h"
#include "ctLog.h"

#include "ctApp.h"

#include "j1Collision.h"
#include "ctInput.h"
#include "ctRender.h"
#include "Entity.h"
#include "j1Printer.h"

j1Collision::j1Collision()
{
	name.assign("collision");

	for (int i = 0; i < ColliderType_MaxColliders; ++i) {
		for (int j = 0; j < ColliderType_MaxColliders; ++j) {
			matrix[i][j] = false;
		}
	}

	// COLLIDERS
	/// Player
	matrix[ColliderType_Player][ColliderType_Inem] = true;
	matrix[ColliderType_Player][ColliderType_Enterprise] = true;
	matrix[ColliderType_Player][ColliderType_XXX] = true;
	matrix[ColliderType_Player][ColliderType_Street] = true;
	matrix[ColliderType_Player][ColliderType_University] = true;
	matrix[ColliderType_Player][ColliderType_DiningRoom] = true;

	matrix[ColliderType_Player][ColliderType_ChangeStreet] = true;
	matrix[ColliderType_Player][ColliderType_ChangeUniversity] = true;
	matrix[ColliderType_Player][ColliderType_ChangeDiningRoom] = true;

	matrix[ColliderType_Player][ColliderType_End] = true;

	// DEBUG COLORS
	// red: player
	// white: buildings
	// blue: change between characters
	// orange: things that happen in the world

	/// Player
	debugColors[ColliderType_Player] = ColorRed;

	/// Buildings
	debugColors[ColliderType_Inem] = ColorGreen;
	debugColors[ColliderType_Enterprise] = ColorGreen;
	debugColors[ColliderType_Street] = ColorGreen;
	debugColors[ColliderType_University] = ColorGreen;
	debugColors[ColliderType_DiningRoom] = ColorGreen;

	/// Change between characters
	debugColors[ColliderType_ChangeStreet] = ColorBlue;
	debugColors[ColliderType_ChangeUniversity] = ColorBlue;
	debugColors[ColliderType_ChangeDiningRoom] = ColorBlue;

	/// End
	debugColors[ColliderType_XXX] = ColorOrange;
	debugColors[ColliderType_End] = ColorOrange;
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	bool ret = true;

	// Remove all colliders scheduled for deletion
	list<Collider*>::iterator it = colliders.begin();

	while (it != colliders.end()) {

		if ((*it)->isRemove) {

			RemoveCollider(*it);

			it = colliders.begin();
			continue;
		}

		it++;
	}

	return ret;
}

// Called before render is available
bool j1Collision::Update(float dt)
{
	bool ret = true;

	list<Collider*>::const_iterator I = colliders.begin();

	while (I != colliders.end()) {

		if (!(*I)->isValid) {

			I++;
			continue;
		}

		list<Collider*>::const_iterator J = I;
		J++;

		// Avoid checking collisions already checked
		while (J != colliders.end()) {

			if ((!matrix[(*I)->colliderType][(*J)->colliderType] && !matrix[(*J)->colliderType][(*I)->colliderType])
				|| !(*J)->isValid) {

				J++;
				continue;
			}

			if ((*I) != nullptr && (*J) != nullptr) {

				if (matrix[(*I)->colliderType][(*J)->colliderType]) {

					// Check if there is a collision between the offsetColliders
					if ((*I)->CheckCollision((*J)->colliderRect) && (*I)->callback != nullptr) {
						// If one of the colliders belongs to a Static Entity, process here the collision (by only checking the offsetColliders)
						if ((*I)->isTrigger) {

							if (find((*I)->collidingGroups.begin(), (*I)->collidingGroups.end(), *J) == (*I)->collidingGroups.end()) {

								(*I)->collidingGroups.push_back(*J);
								(*I)->lastCollidingGroups.push_back(*J);

								// Collision!
								(*I)->callback->OnCollision(*I, *J, CollisionState_OnEnter);
								ret = true;
							}
							else {

								(*I)->lastCollidingGroups.push_back(*J);
								ret = true;
							}
						}
						else
							(*I)->callback->OnCollision(*I, *J, CollisionState_OnEnter);
					}
				}

				if (matrix[(*J)->colliderType][(*I)->colliderType]) {

					// Check if there is a collision between the offsetColliders
					if ((*J)->CheckCollision((*I)->colliderRect) && (*J)->callback != nullptr) {

						// If one of the colliders belongs to a Static Entity, process here the collision (by only checking the offsetColliders)
						if ((*J)->isTrigger) {

							if (find((*J)->collidingGroups.begin(), (*J)->collidingGroups.end(), *I) == (*J)->collidingGroups.end()) {

								(*J)->collidingGroups.push_back(*I);
								(*J)->lastCollidingGroups.push_back(*I);

								// Collision!
								(*J)->callback->OnCollision(*J, *I, CollisionState_OnEnter);
								ret = true;
							}
							else {

								(*J)->lastCollidingGroups.push_back(*I);
								ret = true;
							}
						}
						else
							(*J)->callback->OnCollision(*J, *I, CollisionState_OnEnter);
					}
				}
			}
			J++;
		}
		I++;
	}

	HandleTriggers();

	return ret;
}

void j1Collision::HandleTriggers()
{
	list<Collider*>::const_iterator groups = colliders.begin();

	while (groups != colliders.end()) {

		list<Collider*>::const_iterator collisions = (*groups)->collidingGroups.begin();

		while (collisions != (*groups)->collidingGroups.end()) {

			if (find((*groups)->lastCollidingGroups.begin(), (*groups)->lastCollidingGroups.end(), *collisions) == (*groups)->lastCollidingGroups.end()) {

				// Not collision anymore...
				(*groups)->callback->OnCollision(*groups, *collisions, CollisionState_OnExit);

				(*groups)->collidingGroups.remove(*collisions++);
				continue;
			}
			else
				(*groups)->lastCollidingGroups.remove(*collisions);

			collisions++;
		}
		groups++;
	}
}

// Called before quitting
bool j1Collision::CleanUp()
{
	bool ret = true;

	LOG("Freeing all colliders");

	// Remove all colliderGroups
	list<Collider*>::iterator it = colliders.begin();

	while (it != colliders.end()) {

		delete *it;
		it++;
	}
	colliders.clear();

	return ret;
}

void j1Collision::DebugDraw()
{
	Uint8 alpha = 100;
	SDL_Color color;

	list<Collider*>::const_iterator it = colliders.begin();

	while (it != colliders.end()) {

		color = debugColors[(*it)->colliderType];

		App->printer->PrintQuad((*it)->colliderRect, { color.r,color.g,color.b,alpha }, true, Layers_DebugDraw);

		it++;
	}
}

Collider* j1Collision::CreateCollider(ColliderType colliderType, SDL_Rect colliderRect, ctModule* callback) 
{
	Collider* coll = new Collider(colliderRect, colliderType, callback);

	if (coll != nullptr) {
	
		colliders.push_back(coll);
		return coll;
	}

	return nullptr;
}

bool j1Collision::RemoveCollider(Collider* collider) 
{
	bool ret = false;

	if (collider != nullptr) {
	
		colliders.remove(collider);
		delete collider;

		ret = true;
	}

	return ret;
}

// Collider struct ---------------------------------------------------------------------------------

Collider::Collider(SDL_Rect colliderRect, ColliderType colliderType, ctModule* callback) :colliderRect(colliderRect), colliderType(colliderType), callback(callback) {}

Collider::~Collider()
{
	callback = nullptr;
}

void Collider::SetPos(int x, int y)
{
	colliderRect.x = x;
	colliderRect.y = y;
}

iPoint Collider::GetPos() const
{
	return { colliderRect.x, colliderRect.y };
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (colliderRect.x < r.x + r.w && colliderRect.x + colliderRect.w > r.x && colliderRect.y < r.y + r.h && colliderRect.h + colliderRect.y > r.y);
}