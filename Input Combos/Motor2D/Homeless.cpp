#include "Homeless.h"

Homeless::Homeless(int x, int y, EntityType type) : Player(x, y, type)
{
	anims[Animations::Idle].PushBack({ 552,8,128,376 });
	anims[Animations::Idle].speedFactor = 9.0f;
	anims[Animations::Move].PushBack({ 552,8,128,376 });
//	anims[Animations::Move].PushBack({ 200,104,32,94 });
//	anims[Animations::Move].PushBack({ 240,104,32,94 });
	//anims[Animations::Move].PushBack({ 280,104,32,94 });
	//anims[Animations::Move].PushBack({ 310,104,32,94 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

Homeless::~Homeless()
{
}
