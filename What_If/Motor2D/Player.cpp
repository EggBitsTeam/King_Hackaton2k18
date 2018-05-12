#include "ctApp.h"
#include "Player.h"
#include "ctInput.h"

Player::Player(int x, int y, EntityType type) : Entity(x,y,type)
{
	anims[Animations::Idle].PushBack({ 0,0,0,0 });
	anims[Animations::Move].PushBack({ 0,0,0,0 });
}

Player::~Player()
{
}

void Player::Update(float dt)
{

	switch (statesPlayer)
	{
	case Idle:
		if (App->input->GetAxis(LEFT) == KEY_DOWN || App->input->GetAxis(RIGHT) == KEY_DOWN)
		{
			statesPlayer = PlayerStates::Move_state;
			anim = &anims[Animations::Move];
			break;
		}
		break;

	case Move:
		if (App->input->GetAxis(LEFT) == KEY_UP || App->input->GetAxis(RIGHT) == KEY_UP)
		{
			statesPlayer = PlayerStates::Idle_state;
			anim = &anims[Animations::Idle];
		}
		break;
	}
}
