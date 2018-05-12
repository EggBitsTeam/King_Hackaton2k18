#include "NpcBadBoy.h"

NpcBadBoy::NpcBadBoy(int x, int y, EntityType type) : Entity(x, y, type)
{
	anims[Smoking].PushBack({ 39,149,11,48 });
	anims[Smoking].PushBack({ 52,149,13,50 });
	anims[Smoking].PushBack({ 66,149,13,50 });
	anims[Smoking].PushBack({ 80,149,13,50 });
	anims[Smoking].PushBack({ 94,149,13,50 });
	anims->speedFactor = 9.0f;

	anim = &anims[Smoking];
}

NpcBadBoy::~NpcBadBoy()
{
}

void NpcBadBoy::Update(float dt)
{
	anim->speed = anim->speedFactor * dt;
}
