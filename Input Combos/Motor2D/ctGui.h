#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "ctModule.h"
#include <vector>
#include <string>
#include "ctFonts.h"
#include "ctEntities.h"

struct SDL_Texture;
struct SDL_Rect;
class UIElement;
struct SDL_Color;
class Entity;
struct WorldMapElement;

enum UI_Type
{
	LABEL,
	BUTTON,
	IMAGE,
	TEXTBOX,
	DIALOG,
	CHARACTER_SELECTOR,

	UI_NOT_DEF
};

// ---------------------------------------------------
class ctGui : public ctModule
{

public:

	ctGui();

	// Destructor
	virtual ~ctGui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions

	const SDL_Texture* GetAtlas() const;

	bool DeleteUIElement(UIElement &element);
	bool DeleteAllUIElements();

	UIElement* AddUIDialog(int position_x, int position_y, ctAnimation dialog_animation, ctModule* callback = nullptr, UIElement* parent = nullptr);
	UIElement* AddUICharacterSelector(int position_x, int position_y, SDL_Rect rect, ctModule* callback = nullptr, UIElement* parent = nullptr);

	UIElement* AddUIImage(int position_x, int position_y, SDL_Rect rect, ctModule* callback = nullptr, UIElement* parent = nullptr);
	UIElement* AddUIButton(int position_x, int position_y, SDL_Rect normal_rect, SDL_Rect focused_rect, SDL_Rect pressed_rect, ctModule* callback = nullptr, UIElement* parent = nullptr);
	UIElement* AddUILabel(int position_x, int position_y, std::string text, SDL_Color color, int size, ctModule* callback = nullptr, UIElement* parent = nullptr, const char* path = DEFAULT_FONT, bool UIblit = false);
	UIElement* AddUITextBox(int position_x, int position_y, int size, int box_width, std::string text, SDL_Color color, UIElement* parent = nullptr, const char* path = DEFAULT_FONT);
	UIElement* GetElementUnderMouse(int x, int y);

private:


	std::vector<UIElement*> ui_elements;

	//SDL_Texture* atlas;
	//SDL_Texture* pause_menu_image;
	std::string atlas_file_name;
	std::string pause_menu_image_file_name;
public:
	SDL_Texture* atlas;
	SDL_Texture* pause_menu_image;
};

#endif // __j1GUI_H__