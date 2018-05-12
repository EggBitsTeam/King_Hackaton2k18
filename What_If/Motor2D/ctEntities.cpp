#include "ctApp.h"
#include "ctRender.h"
#include "ctEntities.h"
#include "ctTextures.h"
#include "Entity.h"
#include "ctAudio.h"
#include "ctWindow.h"
#include "ctLog.h"
#include "ctFadeToBlack.h"
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

	//cleric_spritesheet_name = config.child("cleric").attribute("spritesheetName").as_string();
	
	return ret;
}

bool ctEntities::Start()
{
	

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

	for (int i = 0; i <draw_priority_entities.size(); i++)
		if (draw_priority_entities.at(i) != nullptr) draw_priority_entities[i]->Draw();


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


	return true;
}


bool ctEntities:: SpawnEntity(int x, int y, EntityType type)
{
	// find room for the new entity
	bool ret = false;

	switch (type)
	{
	case EntityType::PLAYER: {
		Player* ourPlayer = new Player(x, y, PLAYER);
		entities.push_back(ourPlayer);
		ret = true;
		break;
	}
	default:
		break;
	}

	return ret;
}

