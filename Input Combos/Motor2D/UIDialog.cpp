#include "ctApp.h"
#include "UIDialog.h"
#include "ctLog.h"
#include "ctGui.h"
#include "j1Printer.h"


UIDialog::UIDialog(int x, int y, UI_Type type, ctAnimation dialog_animation, ctModule* callback, UIElement* parent) : UIElement(x, y, type, parent)
{
	this->callback = callback;
	current_animation = &dialog_animation;
}

void UIDialog::Draw(SDL_Texture* sprites)
{
	App->printer->PrintSprite({ (int)this->screen_position.x,(int)this->screen_position.y }, sprites, current_animation->GetCurrentFrame(), 1);
}