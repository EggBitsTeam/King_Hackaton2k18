#include "ctApp.h"
#include "ctEntities.h"
#include "ctTextures.h"
#include "Entity.h"
#include "ctLog.h"
#include "Player.h"

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
	atlasEntities = App->tex->Load("textures/player.png");

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
	case EntityType::PLAYER: {
		toSpawn = new Player(x, y, PLAYER);
		entities.push_back(toSpawn);
		break;
	}
	default:
		break;
	}

	return toSpawn;
}

const SDL_Texture* ctEntities::GetAtlas() const
{
	return atlasEntities;
}
