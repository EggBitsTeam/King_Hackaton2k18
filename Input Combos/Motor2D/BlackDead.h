#ifndef __BLACKDEAD_H__
#define __BLACKDEAD_H__

#include "Entity.h"
#include "ctAnimation.h"

class BlackDead : public Entity
{
public:
	enum Animations
	{
		idle,
		Max_anim,
	};

	ctAnimation anims[Max_anim];

	float speed = 0.0f;
	float speedFactor = 30.0f;

public:
	BlackDead(int x, int y, EntityType type);
	virtual ~BlackDead();
	void Update(float dt);
};

#endif