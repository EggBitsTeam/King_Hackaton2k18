#ifndef __MODULEPRINTER_H__
#define __MODULEPRINTER_H__

#include "Module.h"
#include "Application.h"
#include "p2Point.h"

#include <queue>

class SDL_Texture;

enum Layers
{
	ENTITIES = 0,
};


class DrawingElem
{
public:
	enum class DElemType
	{
		NONE = -1,
		SPRITE,
		QUAD
	} type = DElemType::NONE;
	
public:

	DrawingElem(DElemType type) : type(type) {}
};

class Sprite : public DrawingElem
{
public:

	iPoint pos = { 0,0 };
	SDL_Texture* texture = nullptr;
	SDL_Rect SquaretoBlit = { 0,0,0,0 };
	int layer = 0;
	float angle = 0.0f;
	SDL_Color color = { 0,0,0,0 };

public:

	Sprite(iPoint& pos, SDL_Texture* texture, SDL_Rect& SquaretoBlit, int layer, float angle, SDL_Color color) : DrawingElem(DrawingElem::DElemType::SPRITE), pos(pos), texture(texture), SquaretoBlit(SquaretoBlit), layer(layer), angle(angle), color(color){}

};

class Quad : public DrawingElem
{
public:

	SDL_Rect rect;
	SDL_Color color;
	bool filled;
	bool use_camera;

public:

	Quad(SDL_Rect rect, SDL_Color color, bool filled, bool use_camera) : DrawingElem(DrawingElem::DElemType::QUAD), rect(rect), color(color), filled(filled), use_camera(use_camera) {}

};

class ModulePrinter : public Module
{
public:

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:

	bool PrintSprite(iPoint pos, SDL_Texture* texture, SDL_Rect SquaretoBlit, int layer = 0, float degangle = 0, SDL_Color color = { 255,255,255,255 });
	
	bool PrintQuad(SDL_Rect rect, SDL_Color color, bool filled = false, bool use_camera = false);

private:

	std::priority_queue<DrawingElem*, std::vector<DrawingElem*>, Compare> DrawingQueue;
};


class Compare
{
public:
	bool operator () (DrawingElem* first, DrawingElem* second)
	{
		if (first->type == DrawingElem::DElemType::SPRITE && second->type == DrawingElem::DElemType::SPRITE)
		{
			Sprite* first_Sprite = (Sprite*)first;
			Sprite* second_Sprite = (Sprite*)second;
			if (first_Sprite->layer != second_Sprite->layer)
				return first_Sprite->layer > second_Sprite->layer;
			else
				return true;
		}
		else if (first->type == DrawingElem::DElemType::QUAD && second->type == DrawingElem::DElemType::QUAD)
		{
			Quad* firstQuad = (Quad*)first;
			Quad* secondQuad = (Quad*)second;
			return firstQuad->rect.y + firstQuad->rect.h > secondQuad->rect.y + secondQuad->rect.h;
		}
		else if (first->type == DrawingElem::DElemType::QUAD && second->type == DrawingElem::DElemType::SPRITE)
		{
			return true;
		}
		else if (first->type == DrawingElem::DElemType::SPRITE && second->type == DrawingElem::DElemType::QUAD)
		{
			return false;
		}
	}
};

#endif