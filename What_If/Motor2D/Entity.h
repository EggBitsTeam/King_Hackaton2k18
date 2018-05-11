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
	
	bool key_entities_speed = false;

public:

public:
	ctAnimation* animation = nullptr;

	ctAnimation idle = ctAnimation();
	
	iPoint position = iPoint(0, 0);

	EntityType type = EntityType::NO_TYPE;
	bool to_destroy = false;
	bool flip_texture = false;
	
	SDL_Texture* texture = nullptr;

	//Priority Draw Order
	uint priority_draw_order = 0u;

public:

	Entity(int x, int y, EntityType type);
	virtual ~Entity();

	virtual void Update(float dt) {};
	virtual void Draw();
	virtual void SetEntitiesSpeed(float dt) {};

	virtual void LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation) {};
	bool LoadProperties(pugi::xml_node properties);

};

#endif // __ENTITY_H__