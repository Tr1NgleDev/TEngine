#pragma once

#include "../glm/glm.hpp"

namespace TEngine
{
	struct Rect
	{
		float x, y;
		float w, h;

		Rect();
		Rect(float x, float y, float w, float h);
		Rect(glm::vec2 pos, glm::vec2 size);
	};
	struct IRect
	{
		int x, y;
		int w, h;
		IRect();
		IRect(int x, int y, int w, int h);
		IRect(glm::ivec2 pos, glm::ivec2 size);
	};
}
