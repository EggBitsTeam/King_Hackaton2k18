#ifndef __BULLYBOY2_H__
#define __BULLYBOY2_H__

#include "Entity.h"
#include "ctAnimation.h"

class BullyBoy2 : public Entity
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
	BullyBoy2(int x, int y, EntityType type);
	virtual ~BullyBoy2();
	void Update(float dt);
};

#endif