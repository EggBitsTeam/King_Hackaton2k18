#ifndef __UIDialog_H__
#define __UIDialog_H__

#include "UIElement.h"

class UIDialog: public UIElement
{
private:
	ctAnimation* current_animation;

public:
	UIDialog(int x, int y, UI_Type type, ctAnimation dialog_animation, ctModule* callback, UIElement* parent = nullptr);
	virtual void Draw(SDL_Texture* sprites);
};

#endif //__UIIMAGE_H__