#include "Black.h"

Black::Black(int x, int y, EntityType type) : Player(x,y,type)
{
	anims[Animations::Idle].PushBack({ 1,1,11,48 });
	anims[Animations::Idle].PushBack({ 16,1,11,48 });
	anims[Animations::Idle].speedFactor = 4.5f;
	anims[Animations::Move].PushBack({ 1,51,11,48 });
	anims[Animations::Move].PushBack({ 16,51,11,48 });
	anims[Animations::Move].PushBack({ 32,51,11,48 });
	anims[Animations::Move].PushBack({ 48,51,11,48 });
	anims[Animations::Move].PushBack({ 64,51,11,48 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

Black::~Black()
{
}
