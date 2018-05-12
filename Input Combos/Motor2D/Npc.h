#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"
#include "ctAnimation.h"

class Npc : public Entity
{
public:
	enum Animations
	{
		NoPass,
		Max_anim,
	};

	ctAnimation anims[Max_anim];

	float speed = 0.0f;
	float speedFactor = 30.0f;

public:
	Npc(int x, int y, EntityType type);
	virtual ~Npc();
	void Update(float dt);
};

#endif