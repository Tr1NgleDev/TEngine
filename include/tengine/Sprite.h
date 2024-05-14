#pragma once

#include "GameObject.h"
#include "Color.h"
#include <string>

#include "Axes.h"

namespace TEngine
{
	class Shader;
	class Texture;
	class Sprite : public GameObject
	{
	private:
		bool _antialiased = true;
	public:
		inline static bool instancing = false;
		inline static unsigned int VAO = 0, curVAO = 0;
		inline static unsigned int VBO = 0;
		inline static constexpr uint8_t vertices[] =
		{ 
			0,0, 0,0,
			1,0, 1,0,
			1,1, 1,1,

			//1,1, 1,1,
			0,1, 0,1,
			//0,0, 0,0
		};

		inline static void bindBuffers()
		{
			if (curVAO == VAO) return;

			glBindVertexArray(curVAO = VAO);
		}
		inline static void drawVertices()
		{
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}

		inline static const std::string vertPath = "assets/shaders/spriteVert.glsl";
		inline static const std::string fragPath = "assets/shaders/spriteFrag.glsl";
		inline static const std::string shaderName = "TEngine::SpriteShader";

		inline static const std::string i_vertPath = "assets/shaders/instanced/spriteVert.glsl";
		inline static const std::string i_fragPath = "assets/shaders/instanced/spriteFrag.glsl";
		inline static const std::string i_shaderName = "TEngine::InstancedSpriteShader";

		const Shader* shader;
		Texture* tex;
		Color color;

		bool flipX, flipY;

		glm::vec2 offset{0};

		bool dontRenderOutside = true;

		Sprite(Texture* texture);
		Sprite(const Color& color);
		Sprite(float x, float y);
		Sprite(const glm::vec2& pos);
		Sprite();

		void setAntialiased(bool v);
		bool getAntialiased() const;
		void setGraphicSize(int width, int height = 0);

		static Sprite* createFromTexFile(const std::string& filePath);
		Sprite* loadTex(const std::string& filePath, bool antialiased);
		Sprite* loadTex(const std::string& filePath);
		Sprite* makeGraphic(int w, int h, const Color& color);
		Sprite* makeGraphic(int w, int h);
		Sprite* makeGraphic(const glm::ivec2& size, const Color& color);
		Sprite* makeGraphic(const glm::ivec2& size);

		static void init();

		void screenCenter(Axes axes = Axes::XY, bool basedOnCamera = true);

		void render(double deltaTime) override;
	};
}
