#ifndef __GIRL_H__
#define __GIRL_H__

#include "Player.h"

class Girl : public Player
{
private:

public:
	Girl(int x, int y, EntityType type);
	virtual ~Girl();
};

#endif