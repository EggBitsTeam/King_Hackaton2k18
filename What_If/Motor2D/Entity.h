#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ctPoint.h"
#include "ctAnimation.h"
#include "ctEntities.h"
#include "ctTextures.h"
#include "SDL/include/SDL.h"

#include <vector>

struct SDL_Texture;

class Entity
{
protected:
	ctAnimation* anim = nullptr;
	
	fPoint pos = { 0.0f,0.0f };

	EntityType type = EntityType::NO_TYPE;

	int layerToBlit = 0;

public:
	bool to_destroy = false;

public:

	Entity(int x, int y, EntityType type);
	virtual ~Entity();

	virtual void Update(float dt) {};
	virtual void Draw();

};

#endif // __ENTITY_H__