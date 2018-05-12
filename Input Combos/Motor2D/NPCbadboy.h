#ifndef __NPCBADBOY_H__
#define __NPCBADBOY_H__

#include "Entity.h"
#include "ctAnimation.h"

class NpcBadBoy : public Entity
{
public:
	enum Animations
	{
		Smoking,
		Max_anim,
	};

	ctAnimation anims[Max_anim];

	float speed = 0.0f;
	float speedFactor = 30.0f;

public:
	NpcBadBoy(int x, int y, EntityType type);
	virtual ~NpcBadBoy();
	void Update(float dt);
};

#endif