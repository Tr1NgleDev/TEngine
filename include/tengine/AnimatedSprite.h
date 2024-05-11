#pragma once

#include "BasicIncludes.h"
#include "Sprite.h"
#include "Rect.h"

namespace TEngine
{
	struct Frame
	{
		IRect frame;
		float angle;
		glm::ivec2 offset;
		glm::ivec2 size;

		Frame() {}
		Frame(const IRect& frame, float angle, const glm::ivec2& offset, const glm::ivec2& size);
	};

	class AnimatedSprite : public Sprite
	{
		double time = 0.0;
		uint32_t prevFrame = (uint32_t)-1;
	public:
		inline static const std::string vertPath = Sprite::vertPath;
		inline static const std::string fragPath = "assets/shaders/animSpriteFrag.glsl";
		inline static const std::string shaderName = "TEngine::AnimatedSpriteShader";

		AnimatedSprite();
		AnimatedSprite(const std::string& texPath, const std::string& framesPath);

		double animFPS = 24.0;

		std::unordered_map<std::string, std::vector<Frame>> anims;
		std::unordered_map<std::string, std::string> aliases;
		std::unordered_map<std::string, glm::vec2> offsets;

		std::string curAnim = "";

		bool loop = false;
		bool playing = false;
		bool reversed = false;

		bool isFinished();
		
		void play(const std::string& animName, uint32_t startFrame = 0, double fps = 24.0, bool loop = false, bool reversed = false);
		void resume();
		void stop();
		void pause();

		uint32_t getFrameCount();
		uint32_t getFrameCount(const std::string& animName);
		double getDuration();
		double getDuration(const std::string& animName, double fps = 24.0);

		void setTime(double time);
		double getTime();

		void setFrame(uint32_t frame);
		uint32_t getFrame();

		bool loadFrames(const std::string& path);
		void render(double dt) override;

		void addAlias(const std::string& animName, const std::string& aliasName);
		void addOffset(const std::string& animName, const glm::vec2& offset);
	};
}
