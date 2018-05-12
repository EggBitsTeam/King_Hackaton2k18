#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x, int y, EntityType type);
	virtual ~Player();
	void Update(float dt);
	void Draw();

private:

};

#endif