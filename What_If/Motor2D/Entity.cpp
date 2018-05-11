#include "ctApp.h"
#include "Entity.h"
#include "ctRender.h"
#include "ctAudio.h"
#include "ctLog.h"

//randomize libs
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Entity::Entity(int x, int y, EntityType type) : position(x, y), type(type)
{

	/* initialize random seed: */
	srand(time(NULL));
}

Entity::~Entity()
{
	App->tex->UnLoad(texture);
}

void Entity::Draw()
{
	SDL_Rect r = animation->GetCurrentFrame();
	

	if (animation != nullptr) {
		if (flip_texture == false)
		App->render->Blit(texture, position.x, position.y - r.h, &(animation->GetCurrentFrame()));
		else {
		App->render->Blit(texture, position.x, position.y - r.h, &(animation->GetCurrentFrame()), NULL,NULL,255, SDL_FLIP_HORIZONTAL);
		}
	}

}
