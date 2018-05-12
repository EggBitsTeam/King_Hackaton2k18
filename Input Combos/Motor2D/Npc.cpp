#include "Npc.h"

Npc::Npc(int x, int y, EntityType type) : Entity(x,y,type)
{
	anims[NoPass].PushBack({ 5,151,11,48 });
	anims[NoPass].PushBack({ 20,151,11,48 });
	anims->speedFactor = 9.0f;

	anim = &anims[NoPass];
}

Npc::~Npc()
{
}

void Npc::Update(float dt)
{
	anim->speed = anim->speedFactor * dt;
}
