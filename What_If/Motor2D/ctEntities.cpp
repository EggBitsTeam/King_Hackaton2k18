#include "ctApp.h"
#include "ctRender.h"
#include "ctEntities.h"
#include "ctTextures.h"
#include "Entity.h"
#include "ctAudio.h"
#include "ctWindow.h"
#include "ctLog.h"
#include "ctFadeToBlack.h"


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

	if (entities.size() != draw_priority_entities.size())
	{
		draw_priority_entities = entities;
	}

	OrderDrawEntities();

	
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
	case EntityType::CLERIC: {
		/*Cleric* cleric = new Cleric(x, y, CLERIC);
		entities.push_back(cleric);
		App->combat->turn_priority_entity.push_back(cleric);
		ret = true;*/
		break;
	}
	default:
		break;
	}


	return ret;
}

void ctEntities::OrderDrawEntities()
{
	bool ordered = false;
	
	std::vector<Entity*> order_entity = draw_priority_entities;

	while (!ordered)
	{
   		ordered = true;
		std::vector<Entity*>::iterator itnext = order_entity.begin();
		int count = 0;
		for (std::vector<Entity*>::iterator it = order_entity.begin(); it != order_entity.end(); ++it)
		{
			itnext++;
			count++;
			if (count != order_entity.size())
			{
				if ((*it)->position.y > (*itnext)->position.y )
				{
					Entity* entity_tmp = (*it);

					(*it) = (*itnext);
					it++;
					(*it) = entity_tmp;
					it--;
					ordered = false;

				}
				else if ((*it)->position.y == (*itnext)->position.y)
				{

					if (((*itnext)->type != CLERIC && (*itnext)->type != WARRIOR && (*itnext)->type != ELF && (*itnext)->type != DWARF) && ((*it)->type == CLERIC || (*it)->type == WARRIOR || (*it)->type == ELF || (*it)->type == DWARF))
					{
						Entity* entity_tmp = (*it);

						(*it) = (*itnext);
						it++;
						(*it) = entity_tmp;
						it--;
						ordered = false;
					}
				}
				
			}
			else {
				break;
			}

		}

	}
	ordered = false;





	draw_priority_entities = order_entity;

	order_entity.clear();
}

