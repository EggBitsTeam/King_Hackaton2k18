#include "BullyBoy2.h"

BullyBoy2::BullyBoy2(int x, int y, EntityType type) : Entity(x, y, type)
{
	anims[Animations::idle].PushBack({ 242, 151, 27, 48 });
	anims[Animations::idle].PushBack({ 269, 151, 27, 48 });
	anims[Animations::idle].PushBack({ 296, 150, 27, 48 });
	anims[Animations::idle].PushBack({ 323, 150, 27, 48 });
	anims[Animations::idle].PushBack({ 350, 150, 27, 48 });
	anims[Animations::idle].speedFactor = 9.0f;
}

BullyBoy2::~BullyBoy2()
{
}

void BullyBoy2::Update(float dt)
{
	anim->speed = anim->speedFactor * dt;
}
