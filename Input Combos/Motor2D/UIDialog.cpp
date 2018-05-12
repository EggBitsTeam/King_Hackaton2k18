#include "ctApp.h"
#include "UIDialog.h"
#include "ctLog.h"
#include "ctGui.h"
#include "j1Printer.h"


UIDialog::UIDialog(int x, int y, UI_Type type, ctAnimation dialog_animation, ctModule* callback, UIElement* parent) : UIElement(x, y, type, parent)
{
	this->callback = callback;
	current_animation = dialog_animation;
	current_rect.w = dialog_animation.GetCurrentFrame().w;
	current_rect.h = dialog_animation.GetCurrentFrame().h;
}
