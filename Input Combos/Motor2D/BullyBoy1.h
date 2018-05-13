#ifndef __BULLYBOY1_H__
#define __BULLYBOY1_H__

#include "Entity.h"
#include "ctAnimation.h"

class BullyBoy1 : public Entity
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
	BullyBoy1(int x, int y, EntityType type);
	virtual ~BullyBoy1();
	void Update(float dt);
};

#endif