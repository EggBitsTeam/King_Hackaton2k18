#include "ModulePrinter.h"
#include "ModuleRender.h"

#include "Brofiler\Brofiler.h"

bool ModulePrinter::Awake(pugi::xml_node&)
{
	return true;
}
bool ModulePrinter::Start()
{
	return true;
}
bool ModulePrinter::PreUpdate()
{
	return true;
}
bool ModulePrinter::Update(float dt)
{
	return true;
}
bool ModulePrinter::PostUpdate()
{
	BROFILER_CATEGORY("Printer Blit", Profiler::Color::Azure);

	while (!DrawingQueue.empty())
	{
		DrawingElem* delem = DrawingQueue.top();
		switch (delem->type)
		{
			case DrawingElem::DElemType::SPRITE:
			{
				Sprite* sprite = (Sprite*)delem;
				SDL_SetTextureColorMod(sprite->texture, sprite->color.r, sprite->color.g, sprite->color.b);
				App->render->Blit(sprite->texture, sprite->pos.x, sprite->pos.y, &sprite->SquaretoBlit, 1, 1, sprite->angle);
				SDL_SetTextureColorMod(sprite->texture, 255, 255, 255);
				break;
			}
			case DrawingElem::DElemType::QUAD:
			{
				Quad* quad = (Quad*)delem;
				App->render->DrawQuad(quad->rect, quad->color.r, quad->color.g, quad->color.b, quad->color.a, quad->filled, quad->use_camera);
			}
		}
	
		DrawingQueue.pop();
		delete delem;
	}

	return true;
}

bool ModulePrinter::CleanUp()
{
	while (!DrawingQueue.empty())
	{
		DrawingElem* delem = DrawingQueue.top();
		DrawingQueue.pop();
		delete delem;
	}
	return DrawingQueue.empty();
}

bool ModulePrinter::PrintSprite(iPoint pos, SDL_Texture* texture, SDL_Rect SquaretoBlit, int layer, float degangle, SDL_Color color)
{
	Sprite* sprite = new Sprite(pos, texture, SquaretoBlit, layer, degangle, color);
	DrawingQueue.push(sprite);

	return true;
}

bool ModulePrinter::PrintQuad(SDL_Rect rect, SDL_Color color, bool filled, bool use_camera)
{
	Quad* quad = new Quad(rect, color, filled, use_camera);
	DrawingQueue.push(quad);

	return true;
}