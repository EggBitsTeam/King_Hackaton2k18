#include "White.h"

White::White(int x, int y, EntityType type) : Player(x, y, type)
{
	anims[Animations::Idle].PushBack({ 31,1,15,48 });
	anims[Animations::Idle].PushBack({ 50,1,15,48 });
	anims[Animations::Idle].speedFactor = 4.5f;
	anims[Animations::Move].PushBack({ 342,100,16,48 });
	anims[Animations::Move].PushBack({ 361,100,16,48 });
	anims[Animations::Move].PushBack({ 380,100,16,48 });
	anims[Animations::Move].PushBack({ 399,100,16,48 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

White::~White()
{
}
