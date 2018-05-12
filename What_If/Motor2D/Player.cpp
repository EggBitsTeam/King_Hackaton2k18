#include "ctApp.h"
#include "Player.h"
#include "ctInput.h"
#include "j1Printer.h"

Player::Player(int x, int y, EntityType type) : Entity(x,y,type)
{
	
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	switch (statesPlayer)
	{
	case Idle_state:

		if (App->input->GetAxis(LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			statesPlayer = PlayerStates::Move_state;
			anim = &anims[Animations::Move];
			speed = -speedFactor;
			flipSprite = true;
			break;
		}

		else if (App->input->GetAxis(RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			statesPlayer = PlayerStates::Move_state;
			anim = &anims[Animations::Move];
			speed = speedFactor;
			flipSprite = false;
			break;
		}
		break;

	case Move_state:
		pos.x += speed * dt;
		if (App->input->GetAxis(LEFT) == KEY_UP || App->input->GetAxis(RIGHT) == KEY_UP || App->input->GetKey(SDL_SCANCODE_A) == KEY_UP || App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
		{
			statesPlayer = PlayerStates::Idle_state;
			anim = &anims[Animations::Idle];
		}
		break;

	case Stop_state:


		break;

	case Go_out_state:

		pos.x -= 10.0f * dt;

		break;

	case Enter_state:

		pos.x += 10.0f * dt;

		break;
	}

	anim->speed = anim->speedFactor * dt;
}

void Player::StopPlayer(bool enableCinematic)
{
	if (enableCinematic)
		statesPlayer = Stop_state;
	else
	{
		statesPlayer = Idle_state;
		anim = &anims[Animations::Idle];
	}
}

void  Player::SetAnimation(Animations animToSet)
{
	anim = &anims[animToSet];
}