#include "ctApp.h"
#include "Entity.h"
#include "ctEntities.h"

#include "j1Printer.h"

Entity::Entity(int x, int y, EntityType type) : pos(x, y), type(type)
{
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	App->printer->PrintSprite({(int)pos.x, (int)pos.y}, (SDL_Texture*)App->entities->GetAtlas(), anim->GetCurrentFrame(), layerToBlit);
}
