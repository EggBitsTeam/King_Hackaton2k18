#ifndef __UIDialog_H__
#define __UIDialog_H__

#include "UIElement.h"

class UIDialog: public UIElement
{
private:
	

public:
	UIDialog(int x, int y, UI_Type type, ctAnimation dialog_animation, ctModule* callback, UIElement* parent = nullptr);

};

#endif //__UIIMAGE_H__