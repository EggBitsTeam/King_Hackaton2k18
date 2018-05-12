#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "ctAnimation.h"

class Player : public Entity
{
private:
	enum Animations
	{
		Idle,
		Move,
		Max_anim,
	};

	enum WhoIAm
	{
		No_type,
		White,
		Black,
		Homeless,
		Girl,
	} playerIs = No_type;

	enum PlayerStates
	{
		No_state,
		Idle_state,
		Move_state,
		Cinematic_state
	} statesPlayer = No_state;

	ctAnimation anims[Max_anim];

	float speed = 0.0f;
	float speedFactor = 10.0f;

public:
	Player(int x, int y, EntityType type);
	virtual ~Player();
	void Update(float dt);
	void SetPlayerForCinematic(bool enableCinematic);
	void SetAnimation(Animations animToSet);
	int GetWhoIAm();
};

#endif