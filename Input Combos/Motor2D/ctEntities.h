#ifndef __ctEntities_H__
#define __ctEntities_H__

#include "ctModule.h"
#include "ctAnimation.h"
#include <vector>
#include <string>
#include <queue>

class Entity;

struct SDL_Texture;

enum EntityType
{
	BLACK,
	WHITE,
	GIRL,
	HOMELESS,
	NO_TYPE
};

class ctEntities : public ctModule
{
public:

	ctEntities();
	~ctEntities();

	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool CleanUp();

	Entity* SpawnEntity(int x, int y, EntityType type);

	const SDL_Texture* GetAtlas() const;

	//getters

	std::vector<Entity*> entities;

	SDL_Texture* atlasEntities = nullptr;

};

#endif // __ctEnemies_H__


