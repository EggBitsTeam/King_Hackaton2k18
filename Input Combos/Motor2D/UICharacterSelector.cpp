#include "ctApp.h"
#include "UICharacterSelector.h"
#include "ctLog.h"
#include "ctGui.h"
#include "SceneCity.h"
#include "ctRender.h"
#include "j1Printer.h"


UICharacterSelector::UICharacterSelector(int x, int y, UI_Type type, SDL_Rect rect, ctModule* callback, UIElement* parent) : UIElement(x, y, type, parent)
{
	this->callback = callback;

	current_rect = rect;
	

}

void UICharacterSelector::Update()
{
	switch (App->city->currentPlayer)
	{
	case SceneCity::Current_Player::WHITE_ACTUAL:
		App->printer->PrintQuad({ this->screen_position.x,this->screen_position.y,60,60 }, { 255, 0, 0, 255 }, true, false, Layers_UI);
		break;
	case SceneCity::Current_Player::BLACK_ACTUAL:
		break;
	case SceneCity::Current_Player::HOMELESS_ACTUAL:
		break;
	case SceneCity::Current_Player::GIRL_ACTUAL:
		break;
	default:
		break;
	}
}