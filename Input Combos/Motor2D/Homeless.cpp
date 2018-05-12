#include "Homeless.h"

Homeless::Homeless(int x, int y, EntityType type) : Player(x, y, type)
{
	anims[Animations::Idle].PushBack({ 69,1,16,47 });
	anims[Animations::Idle].PushBack({ 89,1,16,47 });
	anims[Animations::Idle].speedFactor = 4.5f;
	anims[Animations::Move].PushBack({ 80,52,16,47 });
	anims[Animations::Move].PushBack({ 100,50,16,47 });
	anims[Animations::Move].PushBack({ 120,52,16,47 });
	anims[Animations::Move].PushBack({ 140,52,16,47 });
	anims[Animations::Move].PushBack({ 160,52,16,47 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

Homeless::~Homeless()
{
}
