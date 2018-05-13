#ifndef __HOMELESSDEAD_H__
#define __HOMELESSDEAD_H__

#include "Entity.h"
#include "ctAnimation.h"

class HomelessDead : public Entity
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
	HomelessDead(int x, int y, EntityType type);
	virtual ~HomelessDead();
	void Update(float dt);
};

#endif