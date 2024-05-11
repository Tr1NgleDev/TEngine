#include "../include/tengine/Rect.h"

TEngine::Rect::Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

TEngine::Rect::Rect(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

TEngine::Rect::Rect(glm::vec2 pos, glm::vec2 size)
{
	x = pos.x;
	y = pos.y;
	w = size.x;
	h = size.y;
}

TEngine::IRect::IRect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

TEngine::IRect::IRect(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

TEngine::IRect::IRect(glm::ivec2 pos, glm::ivec2 size)
{
	x = pos.x;
	y = pos.y;
	w = size.x;
	h = size.y;
}
