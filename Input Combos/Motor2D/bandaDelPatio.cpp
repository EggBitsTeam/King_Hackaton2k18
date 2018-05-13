#include "bandaDelPatio.h"

bandaDelPatio::bandaDelPatio(int x, int y, EntityType type) : Entity(x, y, type)
{
	anims[idle].PushBack({ 217,25,34,45 });
	anims[idle].PushBack({ 215,77,34,45 });
	anims->speedFactor = 4.5f;

	anim = &anims[idle];
}

bandaDelPatio::~bandaDelPatio()
{
}

void bandaDelPatio::Update(float dt)
{
	anim->speed = anim->speedFactor * dt;
}
