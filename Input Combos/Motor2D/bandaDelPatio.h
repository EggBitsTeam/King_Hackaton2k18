#ifndef __BANDADELPATIO_H__
#define __BANDADELPATIO_H__

#include "Entity.h"
#include "ctAnimation.h"

class bandaDelPatio : public Entity
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
	bandaDelPatio(int x, int y, EntityType type);
	virtual ~bandaDelPatio();
	void Update(float dt);
};

#endif