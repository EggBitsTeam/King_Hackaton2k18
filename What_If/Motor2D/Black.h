#ifndef __BLACK_H__
#define __BLACK_H__

#include "Player.h"

class Black : public Player
{
private:

public:
	Black(int x, int y, EntityType type);
	virtual ~Black();
};

#endif