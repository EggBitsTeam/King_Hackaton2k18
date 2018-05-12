#ifndef __WHITE_H__
#define __WHITE_H__

#include "Player.h"

class White : public Player
{
private:

public:
	White(int x, int y, EntityType type);
	virtual ~White();
};

#endif