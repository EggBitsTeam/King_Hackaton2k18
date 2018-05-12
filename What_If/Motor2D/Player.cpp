#include "ctApp.h"
#include "Player.h"
#include "ctInput.h"

Player::Player(int x, int y, EntityType type) : Entity(x,y,type)
{
	anims[Animations::Idle].PushBack({ 1,1,16,47 });
	anims[Animations::Idle].speedFactor = 9.0f;
	anims[Animations::Move].PushBack({ 18,1,16,47 });
	anims[Animations::Move].PushBack({ 35,1,16,47 });
	anims[Animations::Move].speedFactor = 9.0f;

	statesPlayer = Idle_state;
	anim = &anims[Animations::Idle];
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	switch (statesPlayer)
	{
	case Idle_state:

		if (App->input->GetAxis(LEFT) == KEY_DOWN)
		{
			statesPlayer = PlayerStates::Move_state;
			anim = &anims[Animations::Move];
			speed = -speedFactor;
			break;
		}

		else if (App->input->GetAxis(RIGHT) == KEY_DOWN)
		{
			statesPlayer = PlayerStates::Move_state;
			anim = &anims[Animations::Move];
			speed = speedFactor;
			break;
		}
		break;

	case Move_state:
		pos.x += speed * dt;
		if (App->input->GetAxis(LEFT) == KEY_UP || App->input->GetAxis(RIGHT) == KEY_UP)
		{
			statesPlayer = PlayerStates::Idle_state;
			anim = &anims[Animations::Idle];
		}
		break;
	}

	anim->speed = anim->speedFactor * dt;
}
