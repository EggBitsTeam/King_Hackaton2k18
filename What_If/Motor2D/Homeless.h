#ifndef __HOMELESS_H__
#define __HOMELESS_H__

#include "Player.h"

class Homeless : public Player
{
private:

public:
	Homeless(int x, int y, EntityType type);
	virtual ~Homeless();
};

#endif