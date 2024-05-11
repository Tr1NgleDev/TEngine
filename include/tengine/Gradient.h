#pragma once

#include "BasicIncludes.h"
#include "Sprite.h"
#include "Texture.h"

namespace  TEngine
{
	class Gradient : public Sprite
	{
	public:
		Color gA;
		Color gB;
		float gScale = 1;
		float gOffset;

		inline static const std::string vertPath = Sprite::vertPath;
		inline static const std::string fragPath = "assets/shaders/gradientFrag.glsl";
		inline static const std::string shaderName = "TEngine::GradientShader";

		Gradient(float x, float y, int w, int h);

		void render(double deltaTime) override;
	};
}
