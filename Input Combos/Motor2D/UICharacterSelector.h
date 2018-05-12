#ifndef __UICharacter_H__
#define __UICharacter_H__

#include "UIElement.h"

class UICharacterSelector : public UIElement
{

public:
	UICharacterSelector(int x, int y, UI_Type type, SDL_Rect rect, ctModule* callback, UIElement* parent = nullptr);

	void Update();
};

#endif //__UIIMAGE_H__