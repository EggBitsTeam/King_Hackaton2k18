#include "Girl.h"

Girl::Girl(int x, int y, EntityType type) : Player(x, y, type)
{
	anims[Animations::Idle].PushBack({ 109,1,14,48 });
	anims[Animations::Idle].PushBack({ 127,1,14,48 });
	anims[Animations::Idle].speedFactor = 4.5f;
	anims[Animations::Move].PushBack({ 94,100,14,49 });
	anims[Animations::Move].PushBack({ 112,100,14,49 });
	anims[Animations::Move].PushBack({ 130,100,14,49 });
	anims[Animations::Move].PushBack({ 148,100,14,49 });
	anims[Animations::Move].PushBack({ 164,100,14,49 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

Girl::~Girl()
{
}
