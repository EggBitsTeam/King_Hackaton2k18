#include "ctDefs.h"
#include "ctLog.h"

#include "ctApp.h"

#include "j1Collision.h"
#include "ctInput.h"
#include "ctRender.h"
#include "Entity.h"
#include "j1Printer.h"

#include "Brofiler\Brofiler.h"

j1Collision::j1Collision()
{
	name.assign("collision");

	// COLLIDERS
	/// Player
	matrix[ColliderType_Player][ColliderType_Player] = false;
	matrix[ColliderType_Player][ColliderType_Inem] = false;
	matrix[ColliderType_Player][ColliderType_Enterprise] = false;
	matrix[ColliderType_Player][ColliderType_XXX] = false;
	matrix[ColliderType_Player][ColliderType_Barrio] = false;
	matrix[ColliderType_Player][ColliderType_University] = false;
	matrix[ColliderType_Player][ColliderType_DiningRoom] = false;

	/// Inem
	matrix[ColliderType_Inem][ColliderType_Inem] = false;
	matrix[ColliderType_Inem][ColliderType_Player] = false;
	matrix[ColliderType_Inem][ColliderType_Enterprise] = false;
	matrix[ColliderType_Inem][ColliderType_XXX] = false;
	matrix[ColliderType_Inem][ColliderType_Barrio] = false;
	matrix[ColliderType_Inem][ColliderType_University] = false;
	matrix[ColliderType_Inem][ColliderType_DiningRoom] = false;

	/// Enterprise
	matrix[ColliderType_Enterprise][ColliderType_Enterprise] = false;
	matrix[ColliderType_Enterprise][ColliderType_Inem] = false;
	matrix[ColliderType_Enterprise][ColliderType_Player] = false;
	matrix[ColliderType_Enterprise][ColliderType_XXX] = false;
	matrix[ColliderType_Enterprise][ColliderType_Barrio] = false;
	matrix[ColliderType_Enterprise][ColliderType_University] = false;
	matrix[ColliderType_Enterprise][ColliderType_DiningRoom] = false;

	/// XXX
	matrix[ColliderType_XXX][ColliderType_XXX] = false;
	matrix[ColliderType_XXX][ColliderType_Enterprise] = false;
	matrix[ColliderType_XXX][ColliderType_Inem] = false;
	matrix[ColliderType_XXX][ColliderType_Player] = false;
	matrix[ColliderType_XXX][ColliderType_Barrio] = false;
	matrix[ColliderType_XXX][ColliderType_University] = false;
	matrix[ColliderType_XXX][ColliderType_DiningRoom] = false;

	/// Barrio
	matrix[ColliderType_Barrio][ColliderType_Barrio] = false;
	matrix[ColliderType_Barrio][ColliderType_Enterprise] = false;
	matrix[ColliderType_Barrio][ColliderType_Inem] = false;
	matrix[ColliderType_Barrio][ColliderType_Player] = false;
	matrix[ColliderType_Barrio][ColliderType_XXX] = false;
	matrix[ColliderType_Barrio][ColliderType_University] = false;
	matrix[ColliderType_Barrio][ColliderType_DiningRoom] = false;

	/// University
	matrix[ColliderType_University][ColliderType_University] = false;
	matrix[ColliderType_University][ColliderType_Enterprise] = false;
	matrix[ColliderType_University][ColliderType_Inem] = false;
	matrix[ColliderType_University][ColliderType_Player] = false;
	matrix[ColliderType_University][ColliderType_XXX] = false;
	matrix[ColliderType_University][ColliderType_Barrio] = false;
	matrix[ColliderType_University][ColliderType_DiningRoom] = false;

	/// Dining Room
	matrix[ColliderType_DiningRoom][ColliderType_DiningRoom] = false;
	matrix[ColliderType_DiningRoom][ColliderType_Enterprise] = false;
	matrix[ColliderType_DiningRoom][ColliderType_Inem] = false;
	matrix[ColliderType_DiningRoom][ColliderType_Player] = false;
	matrix[ColliderType_DiningRoom][ColliderType_XXX] = false;
	matrix[ColliderType_DiningRoom][ColliderType_Barrio] = false;
	matrix[ColliderType_DiningRoom][ColliderType_University] = false;
	
	// DEBUG COLORS
	debugColors[ColliderType_Player] = ColorDarkBlue;
	debugColors[ColliderType_Inem] = ColorDarkRed;
	debugColors[ColliderType_Enterprise] = ColorWhite;
	debugColors[ColliderType_XXX] = ColorDarkBlue;
	debugColors[ColliderType_Barrio] = ColorDarkRed;
	debugColors[ColliderType_University] = ColorWhite;
	debugColors[ColliderType_DiningRoom] = ColorLightBlue;
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	BROFILER_CATEGORY(__FUNCTION__, Profiler::Color::Orchid);

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
	BROFILER_CATEGORY(__FUNCTION__, Profiler::Color::Orchid);

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
	BROFILER_CATEGORY(__FUNCTION__, Profiler::Color::Orchid);

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
	BROFILER_CATEGORY(__FUNCTION__, Profiler::Color::Orchid);

	Uint8 alpha = 60;
	SDL_Color color;

	list<Collider*>::const_iterator it = colliders.begin();

	while (it != colliders.end()) {

		color = debugColors[(*it)->colliderType];

		App->printer->PrintQuad((*it)->colliderRect, { color.r,color.g,color.b,alpha }, true);

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