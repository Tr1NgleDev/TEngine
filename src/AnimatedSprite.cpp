#include "../include/tengine/AnimatedSprite.h"
#include "../include/tengine/IO/File.h"
#include "../include/json.hpp"

using namespace TEngine;

Frame::Frame(const IRect& frame, float angle, const glm::ivec2& offset, const glm::ivec2& size) 
	: frame(frame), angle(angle), offset(offset), size(size)
{
}

AnimatedSprite::AnimatedSprite()
{
	shader = Shader::get(AnimatedSprite::shaderName);
}

AnimatedSprite::AnimatedSprite(const std::string& texPath, const std::string& framesPath)
{
	tex = Texture::get(texPath, true);
	setAntialiased(!MainGame::getInstance()->curSmthState->pixelPerfect);

	shader = Shader::get(AnimatedSprite::shaderName);

	loadFrames(framesPath);
}

bool AnimatedSprite::isFinished()
{
	return getFrame() == (!reversed ? getFrameCount() - 1 : 0);
}

void AnimatedSprite::play(const std::string& animName, uint32_t startFrame, double fps, bool loop, bool reversed)
{
	this->reversed = reversed;
	this->loop = loop;
	this->animFPS = fps;
	this->curAnim = animName;
	this->playing = true;
	setFrame(!reversed ? startFrame : getFrameCount() - 1 - startFrame);
}

void AnimatedSprite::resume()
{
	this->playing = true;
}

void AnimatedSprite::pause()
{
	this->playing = false;
}

void AnimatedSprite::stop()
{
	setFrame(!reversed ? 0 : getFrameCount() - 1);
	this->playing = false;
}

uint32_t AnimatedSprite::getFrameCount(const std::string& animName)
{
	if (anims.contains(animName))
		return anims[animName].size();
	else if (aliases.contains(animName) && anims.contains(aliases[animName]))
		return anims[aliases[animName]].size();
	else
		return 0;
}

uint32_t AnimatedSprite::getFrameCount()
{
	return getFrameCount(curAnim);
}

double AnimatedSprite::getDuration(const std::string& animName, double fps)
{
	return (double)getFrameCount(animName) / fps;
}

double AnimatedSprite::getDuration()
{
	return getDuration(curAnim, animFPS);
}

double AnimatedSprite::getTime()
{
	return time;
}

void AnimatedSprite::setTime(double time)
{
	this->time = time;
}

uint32_t AnimatedSprite::getFrame()
{
	return min((uint32_t)max(time * animFPS, 0.0), getFrameCount() - 1);
}

void AnimatedSprite::setFrame(uint32_t frame)
{
	this->time = (double)frame / animFPS;
}

bool AnimatedSprite::loadFrames(const std::string& path)
{
	if (!IO::File::exists(path))
		return false;

	std::string file = IO::File::readAllText(path);

	nlohmann::json json = nlohmann::json::parse(file);
	if (json.is_null()) return false;
	if (!json.contains("frames")) return false;
	if(!json["frames"].is_object()) return false;

	for (auto& frame : json["frames"].items())
	{
		std::string frameName = frame.key();
		std::string animName = frameName.substr(0, frameName.size() - 4);

		bool rotated = frame.value()["rotated"];

		IRect frameRect;
		frameRect.x = frame.value()["frame"]["x"];
		frameRect.y = frame.value()["frame"]["y"];
		frameRect.w = !rotated ? frame.value()["frame"]["w"] : frame.value()["frame"]["h"];
		frameRect.h = !rotated ? frame.value()["frame"]["h"] : frame.value()["frame"]["w"];

		glm::ivec2 offset;
		offset.x = frame.value()["spriteSourceSize"]["x"];
		offset.y = frame.value()["spriteSourceSize"]["y"];

		glm::ivec2 size;
		size.x = frame.value()["sourceSize"]["w"];
		size.y = frame.value()["sourceSize"]["h"];

		Frame frameF = Frame(frameRect, rotated ? -90 : 0, offset, size);

		if(!anims.contains(animName))
			anims[animName] = {};

		anims[animName].push_back(frameF);
	}
	/*
	for (auto& anim : anims)
	{
		Console::print(std::format("\n\nanimName:{}", anim.first), Console::GREEN, Console::BRIGHT);
		int i = 0;
		for (auto& frame : anim.second)
		{
			Console::print(std::format("\n\tframe{}:\n\t\trect:{};{} {}x{}\n\t\tangle:{:.1f}\n\t\toffset:{};{}\n\t\tsize:{}x{}", 
				i, 
				frame.frame.x, frame.frame.y, frame.frame.w, frame.frame.h,
				frame.angle,
				frame.offset.x, frame.offset.y,
				frame.size.x, frame.size.y), Console::CYAN, Console::BRIGHT);

			i++;
		}
	}
	*/
	return true;
}

void AnimatedSprite::render(double dt)
{
	std::string animName = curAnim;
	if (aliases.contains(curAnim) && anims.contains(aliases[curAnim]))
		animName = aliases[curAnim];

	if (!anims.contains(animName))
		return;
	if (playing)
	{
		if(time >= 0.0 && time <= getDuration())
			time += dt * (reversed ? -1 : 1);
	}

	uint32_t frameI = getFrame();

	Frame& frame = anims[animName][frameI];

	glm::ivec2 texSize = tex->getSize();

	GameObject::render(dt);

	bindBuffers();
	shader->use();

	shader->setUniform("scale", glm::vec2((float)frame.frame.w * scale.x, (float)frame.frame.h * scale.y));
	shader->setUniform("offset", -offset);
	shader->setUniform("position", parallaxPos() + glm::vec2(frame.offset) - offsets[animName]);
	shader->setUniform("angle", glm::radians(angle + frame.angle));
	shader->setUniform("targetScale", state->targetScale);
	shader->setUniform("pixelPerfect", state->pixelPerfect);

	shader->setUniform("frame", glm::ivec4(frame.frame.x, frame.frame.y, frame.frame.w, frame.frame.h));
	shader->setUniform("texSize", texSize);

	shader->setUniform("projection", state->projMat, false);
	shader->setUniform("view", state->viewMat, false);
	shader->setUniform("color", color);
	shader->setUniform("time", (float)MainGame::getInstance()->getTime());
	shader->setUniform("flip", glm::vec2{ flipX ? 1.f : 0.f, flipY ? 1.f : 0.f });
	shader->setUniform("bitmap", 0);
	tex->use();
	drawVertices();

	if (loop && frameI == getFrameCount() - 1)
		time = 0;

	prevFrame = frameI;

	//Sprite::render(dt);
}

void AnimatedSprite::addAlias(const std::string& animName, const std::string& aliasName)
{
	aliases[aliasName] = animName;
}
void AnimatedSprite::addOffset(const std::string& animName, const glm::vec2& offset)
{
	std::string animNameA = animName;
	if (aliases.contains(animName) && anims.contains(aliases[animName]))
		animNameA = aliases[animName];

	offsets[animNameA] = offset;
}