#include "ctApp.h"
#include "ctEntities.h"
#include "ctTextures.h"
#include "Entity.h"
#include "ctLog.h"
#include "Player.h"
#include "Black.h"
#include "White.h"
#include "Girl.h"
#include "Homeless.h"
#include "Npc.h"
#include "NPCbadboy.h"
#include "bandaDelPatio.h"

ctEntities::ctEntities()
{
	name = "entities";
}

// Destructor
ctEntities::~ctEntities()
{
	LOG("Unloading entities spritesheet");
}

bool ctEntities::Awake(pugi::xml_node& config)
{
	LOG("Loading Entities from config file");
	bool ret = true;
	
	return ret;
}

bool ctEntities::Start()
{
	atlasEntities = App->tex->Load("textures/characters_spritesheets.png");

	return true;
}

bool ctEntities::PreUpdate()
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->to_destroy) {
			delete(entities[i]);
			entities[i] = nullptr;
			entities.erase(entities.cbegin() + i);
			entities.shrink_to_fit();
		}
	}

	return true;
}

// Called before render is available
bool ctEntities::Update(float dt)
{
	for (int i = 0; i < entities.size(); i++)
		if (entities.at(i) != nullptr) entities[i]->Update(dt);

	for (int i = 0; i <  entities.size(); i++)
		if (entities.at(i) != nullptr) entities[i]->Draw();

	return true;
}

// Called before quitting
bool ctEntities::CleanUp()
{
	LOG("Freeing all entities");

	for (uint i = 0; i < entities.size(); ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
			entities.erase(entities.cbegin() + i);
			entities.shrink_to_fit();
		}
	}

	entities.clear();

	App->tex->UnLoad(atlasEntities);

	return true;
}


Entity* ctEntities:: SpawnEntity(int x, int y, EntityType type)
{
	// find room for the new entity
	bool ret = true;
	Entity* toSpawn = nullptr;
	switch (type)
	{
	case EntityType::HOMELESS:
		toSpawn = new Homeless(x, y, HOMELESS);
		entities.push_back(toSpawn);
		break;

	case EntityType::BLACK:
		toSpawn = new Black(x, y, BLACK);
		entities.push_back(toSpawn);
		break;

	case EntityType::GIRL:
		toSpawn = new Girl(x, y, GIRL);
		entities.push_back(toSpawn);
		break;

	case EntityType::WHITE:
		toSpawn = new White(x, y, WHITE);
		entities.push_back(toSpawn);
		break;

	case EntityType::NPC:
		toSpawn = new Npc(x, y, NPC);
		entities.push_back(toSpawn);
		break;

	case EntityType::NPCBADBOY:
		toSpawn = new NpcBadBoy(x, y, NPCBADBOY);
		entities.push_back(toSpawn);
		break;

	case EntityType::BANDADELPATIO:
		toSpawn = new bandaDelPatio(x, y, BANDADELPATIO);
		entities.push_back(toSpawn);
		break;

	case EntityType::BULLYBOY1:
		toSpawn = new bandaDelPatio(x, y, BULLYBOY1);
		entities.push_back(toSpawn);
		break;

	case EntityType::BULLYBOY2:
		toSpawn = new bandaDelPatio(x, y, BULLYBOY2);
		entities.push_back(toSpawn);
		break;
	default:
		break;
	}

	return toSpawn;
}

const SDL_Texture* ctEntities::GetAtlas() const
{
	return atlasEntities;
}
