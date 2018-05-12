#include "Black.h"

Black::Black(int x, int y, EntityType type) : Player(x,y,type)
{
	anims[Animations::Idle].PushBack({ 1,1,16,47 });
	anims[Animations::Idle].speedFactor = 9.0f;
	anims[Animations::Move].PushBack({ 18,1,16,47 });
	anims[Animations::Move].PushBack({ 35,1,16,47 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

Black::~Black()
{
}
