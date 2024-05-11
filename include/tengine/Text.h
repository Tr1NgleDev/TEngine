#pragma once

#include "Axes.h"
#include "BasicIncludes.h"
#include "Color.h"
#include "GameObject.h"
#include "../sdl2_ttf/SDL_ttf.h"

namespace TEngine
{
	class Shader;
	class Text : public GameObject
	{
		struct TexData
		{
			unsigned int texID;
			float y;
			float w, h;
		};
		
		int linesCount = 0;
		std::string _text;
		std::string _fontPath;
		int _fontSize = 16;
		float _targetScale = 1;
		int _quality = 2;

		TTF_Font* ttfFont;
		SDL_Surface* initial;
		SDL_Surface* intermediary;
		float width;
		float height;

		void loadFont();

		std::vector<TexData> linesTex;

		bool needToUpdateTex = true;
		void updateTex();

		friend GameState;
	public:
		const Shader* shader;
		Color color;
		glm::vec2 offset{ 0 };
		bool flipX, flipY;
		// if 0,0 then there wont be any shadow rendering
		glm::vec2 shadowOffset{ 0 };
		Color shadowColor;

		std::string getText() const;
		void setText(const std::string& text);

		std::string getFontPath() const;
		void setFontPath(const std::string& fontPath);

		int getFontSize() const;
		void setFontSize(int fontSize);

		int getQuality() const;
		void setQuality(int quality);

		void screenCenter(Axes axes = Axes::XY, bool basedOnCamera = true);

		glm::vec2 getSize() const;
		float getWidth() const;
		float getHeight() const;

		Text(float x = 0, float y = 0, const std::string& text = "", const std::string& fontPath = "", int fontSize = 16);

		void destroy() override;
		void render(double deltaTime) override;
	};
}
