#include "HomelessDead.h"

HomelessDead::HomelessDead(int x, int y, EntityType type) : Entity(x, y, type)
{
	anims[Animations::idle].PushBack({ 107, 150, 27, 49 });
	anims[Animations::idle].PushBack({ 134, 151, 27, 49 });
	anims[Animations::idle].PushBack({ 161, 150, 27, 49 });
	anims[Animations::idle].PushBack({ 188, 150, 27, 49 });
	anims[Animations::idle].PushBack({ 215, 150, 27, 49 });
	anims[Animations::idle].speedFactor = 9.0f;

	anim = &anims[Animations::idle];
}

HomelessDead::~HomelessDead()
{
}

void HomelessDead::Update(float dt)
{
	anim->speed = anim->speedFactor * dt;
}
