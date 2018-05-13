#include "WomanFat.h"

WomanFat::WomanFat(int x, int y, EntityType type) : Entity(x, y, type)
{
	anims[Animations::idle].PushBack({ 145, 1, 15, 48 });
	anims[Animations::idle].PushBack({ 163, 1, 15, 48 });
	anims[Animations::idle].speedFactor = 4.0f;

	anim = &anims[Animations::idle];
	flipSprite = true;
}

WomanFat::~WomanFat()
{
}

void WomanFat::Update(float dt)
{
	anim->speed = anim->speedFactor * dt;
}
