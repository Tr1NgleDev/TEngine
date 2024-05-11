#pragma once

#include <functional>
#include <string>

#include "Action.h"

namespace TEngine
{
	class GameState;
	class Shader;
	class RenderTexture
	{
	private:
		float _resScale = 1;
		bool _disposed = false;

	public:
		inline static constexpr int8_t vertices[] = 
		{
			-1,-1, 0,0,
			1,-1,  1,0,
			1,1,   1,1,

			//1,1,   1,1,
			-1,1,  0,1,
			//-1,-1, 0,0
		};

		inline static const std::string vertPath = "assets/shaders/renderTexVert.glsl";
		inline static const std::string fragPath = "assets/shaders/renderTexFrag.glsl";
		inline static const std::string shaderName = "TEngine::RenderTextureShader";

		const Shader* shader;

		unsigned int texID;
		unsigned int fbo;

		int w = 1, h = 1;

		bool useScreenRes = false;

		GameState* state;

		unsigned int VAO, VBO;

		Action<void(RenderTexture* renderTex)> updated;

		float getResScale() const;
		void setResScale(float resScale);

		void init(int w, int h);

		void dispose(bool changeVal);

		RenderTexture(const RenderTexture& other);
		RenderTexture(RenderTexture&& other) noexcept;
		RenderTexture& operator=(const RenderTexture& other);
		RenderTexture& operator=(RenderTexture&& other) noexcept;

		~RenderTexture();

		RenderTexture();

		RenderTexture(GameState* state, float resScale = 1, const std::string& shaderName = RenderTexture::shaderName);
		RenderTexture(GameState* state, float resScale, const std::string& vertPath, const std::string& fragPath, const std::string& shaderName);

		RenderTexture(GameState* state, int w, int h, const std::string& shaderName = RenderTexture::shaderName);
		RenderTexture(GameState* state, int w, int h, const std::string& vertPath, const std::string& fragPath, const std::string& shaderName);
		void resized();

		// Call this before rendering anything (the color values are for glClearColor)
		void renderBegin(float r, float g = 0, float b = 0, float a = 0);
		// Call this before rendering anything (doesnt call glClearColor or glClear)
		void renderBegin();

		// Call this after rendering anything. If <paramref name="displayQuad"/> is true then it will display rendered texture to the DEFAULT Framebuffer
		void renderEnd(bool displayQuad = false);

		void render(std::function<void()> renderFunction);
	};
}
