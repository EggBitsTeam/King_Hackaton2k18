#ifndef __WOMANFAT_H__
#define __WOMANFAT_H__

#include "Entity.h"
#include "ctAnimation.h"

class WomanFat : public Entity
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
	WomanFat(int x, int y, EntityType type);
	virtual ~WomanFat();
	void Update(float dt);
};

#endif