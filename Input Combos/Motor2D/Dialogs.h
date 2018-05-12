#ifndef __Dialogs_H__
#define __Dialogs_H__

#include "ctModule.h"
#include <vector>
#include "ctAnimation.h"

struct SDL_Texture;

class Dialogs : public ctModule
{
public:

	Dialogs();

	// Destructor
	virtual ~Dialogs();

	// Called before render is available
	bool Awake(pugi::xml_node&);
	bool Start();

	// Called before quitting
	bool CleanUp();

	void LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation);

	SDL_Texture* atlas = nullptr;
public:

	ctAnimation tom_01;
};

#endif // __ctAUDIO_H__