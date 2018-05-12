#ifndef __Dialogs_H__
#define __Dialogs_H__

#include "ctModule.h"
#include <vector>
#include "ctAnimation.h"

class Dialogs : public ctModule
{
public:

	Dialogs();

	// Destructor
	virtual ~Dialogs();

	// Called before render is available
	bool Awake(pugi::xml_node&);


	// Called before quitting
	bool CleanUp();

	void LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation);
public:

	ctAnimation tom_01;
};

#endif // __ctAUDIO_H__