#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "ctAnimation.h"

class Player : public Entity
{
public:
	enum Animations
	{
		Idle,
		Move,
		Max_anim,
	};

	enum PlayerStates
	{
		No_state,
		Idle_state,
		Move_state,
		Go_out_state,
		Enter_state,
		Stop_state
	} statesPlayer = No_state;

	ctAnimation anims[Max_anim];

	float speed = 0.0f;
	float speedFactor = 10.0f;

public:
	Player(int x, int y, EntityType type);
	virtual ~Player();
	void Update(float dt);
	void StopPlayer(bool enableCinematic);
	void SetAnimation(Animations animToSet);
};

#endif