#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "p2Point.h"

#include "Animation.h"

class GUIWindow;
class PlayerEntity;
class ChestEntity;
class PortalEntity;
class Guldan;
class Item;

class Scene : public Module
{
public:

	Scene();
	virtual ~Scene();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();
};

#endif