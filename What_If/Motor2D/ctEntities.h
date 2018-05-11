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
	CLERIC,
	DWARF,
	ELF,
	WARRIOR,

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

	bool SpawnEntity(int x, int y, EntityType type);
	
	void OrderDrawEntities();

	//getters

	std::vector<Entity*> entities;
	std::vector<Entity*> draw_priority_entities;

private:

	

public:


};

#endif // __ctEnemies_H__


