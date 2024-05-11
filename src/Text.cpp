#include "../include/tengine/Text.h"

#include "../include/tengine/Shader.h"

using namespace TEngine;

Text::Text(float x, float y, const std::string& text, const std::string& fontPath, int fontSize)
{
	this->shadowColor = Color::Black();
	this->color = Color::White();
	setPos(x, y);
	setText(text);
	setFontPath(fontPath);
	setFontSize(fontSize);
	shader = Shader::get(Sprite::shaderName);
}

void Text::destroy()
{
	GameObject::destroy();

	if (initial != nullptr)
	{
		SDL_FreeSurface(initial);
		initial = nullptr;
	}
	if (intermediary != nullptr)
	{
		SDL_FreeSurface(intermediary);
		intermediary = nullptr;
	}
	if (ttfFont != nullptr)
	{
		TTF_CloseFont(ttfFont);
		ttfFont = nullptr;
	}

	for (auto& tex : linesTex)
		glDeleteTextures(1, &tex.texID);

	linesTex.clear();
}

void Text::render(double deltaTime)
{
	GameObject::render(deltaTime);

	if (state == nullptr)
		state = MainGame::getInstance()->curSmthState;

	if(_targetScale != state->targetScale)
	{
		_targetScale = state->targetScale;
		TTF_SetFontSize(ttfFont, (int)((float)_fontSize * _targetScale) * _quality);
		needToUpdateTex = true;
	}

	if (needToUpdateTex)
	{
		needToUpdateTex = false;
		updateTex();
	}

	// bind quad buffers
	Sprite::bindBuffers();

	// bind shader and apply some uniforms
	shader->use();
	shader->setUniform("projection", state->projMat, false);
	shader->setUniform("view", state->viewMat, false);
	shader->setUniform("color", color);
	shader->setUniform("time", (float)MainGame::getInstance()->getTime());
	shader->setUniform("flip", glm::vec2{ flipX ? 1.f : 0.f, flipY ? 1.f : 0.f });
	shader->setUniform("bitmap", 0);

	// loop over all lines (their textures)
	for(auto& tex : linesTex)
	{
		// update transform matrix if needed
		/*
		if (_updateTransform)
		{
			if (!state->pixelPerfect)
			{
				tex.transform = Utils::createScale(tex.w * scale.x / _targetScale / (float)_quality, tex.h * scale.y / _targetScale / (float)_quality);
				Utils::translate(tex.transform, -offset.x * (tex.w * scale.x / _targetScale / (float)_quality), -offset.y * (float)linesCount * (tex.h * scale.y / _targetScale / (float)_quality) + (tex.y * scale.y));
				Utils::rotate(tex.transform, glm::radians(angle));
				Utils::translate(tex.transform, position.x, position.y);
			}
			else
			{
				tex.transform = Utils::createScale(floorf(tex.w * scale.x / _targetScale / (float)_quality), floorf(tex.h * scale.y / _targetScale / (float)_quality));
				Utils::translate(tex.transform, floorf(-offset.x * (tex.w * scale.x / _targetScale / (float)_quality)), floorf(-offset.y * (float)linesCount * (tex.h * scale.y / _targetScale / (float)_quality) + (tex.y * scale.y)));
				Utils::rotate(tex.transform, glm::radians(angle));
				Utils::translate(tex.transform, floorf(position.x), floorf(position.y));
			}
			Utils::scale(tex.transform, _targetScale, _targetScale);
		}*/
		glm::vec2 scaleShit = glm::vec2(tex.w * scale.x / _targetScale / (float)_quality, tex.h * scale.y / _targetScale / (float)_quality);
		shader->setUniform("scale", scaleShit);
		shader->setUniform("offset", glm::vec2(-offset.x, -offset.y * (float)linesCount + (tex.y * scale.y / scaleShit.y)));
		shader->setUniform("angle", glm::radians(angle));
		shader->setUniform("targetScale", state->targetScale);
		shader->setUniform("pixelPerfect", state->pixelPerfect);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex.texID); // bind text's texture
		Texture::curTex = tex.texID;

		// shadow
		if (shadowOffset.x != 0 || shadowOffset.y != 0)
		{
			//glm::mat4 transformShadow = tex.transform;
			//Utils::translate(transformShadow, shadowOffset.x * scale.x * _targetScale, shadowOffset.y * scale.y * _targetScale);

			shader->setUniform("position", parallaxPos(position + shadowOffset));
			//shader->setUniform("transform", transformShadow, false);
			shader->setUniform("color", shadowColor * color.a);

			Sprite::drawVertices(); // draw quad
		}

		shader->setUniform("color", color);
		shader->setUniform("position", parallaxPos());

		//shader->setUniform("transform", tex.transform, false);

		Sprite::drawVertices(); // draw quad
	}
}

std::string Text::getFontPath() const
{
	return _fontPath;
}

int Text::getFontSize() const
{
	return _fontSize;
}

float Text::getHeight() const
{
	return height;
}

float Text::getWidth() const
{
	return width;
}

glm::vec2 Text::getSize() const
{
	return { width, height };
}

std::string Text::getText() const
{
	return _text;
}

int Text::getQuality() const
{
	return _quality;
}

void Text::setQuality(int quality)
{
	if(_quality != quality)
	{
		_quality = quality;
		TTF_SetFontSize(ttfFont, (int)((float)_fontSize * _targetScale) * _quality);
		needToUpdateTex = true;
	}
}

// loads font from file
void Text::loadFont()
{
	if (ttfFont != nullptr)
	{
		TTF_CloseFont(ttfFont);
		ttfFont = nullptr;
	}

	auto fullPath = std::filesystem::current_path() / _fontPath;
	const char* fullPathCStr = (fullPath.string()).c_str();

	ttfFont = TTF_OpenFont(fullPathCStr, (int)((float)_fontSize * _targetScale) * _quality);

	if (ttfFont == nullptr)
		Console::print(CMode(RED, BLINKING), std::format("TEngine::Text::loadFont(): Couldn't load font!\nSDL_TTF Error:{}\n", TTF_GetError()));
}

void Text::screenCenter(Axes axes, bool basedOnCamera)
{
	if (axes != Axes::Y)
	{
		if (!basedOnCamera)
			position.x = ((float)state->w / 2.f) - (width * scale.x / 2.f);
		else
			position.x = (state->getLeft() + state->getRight()) / 2.f - (width * scale.x / 2.f);
	}
	if (axes != Axes::X)
	{
		if (!basedOnCamera)
			position.y = ((float)state->h / 2.f) - (height * scale.y / 2.f);
		else
			position.y = (state->getBottom() + state->getTop()) / 2.f - (height * scale.y / 2.f);
	}
}

void Text::setFontPath(const std::string& fontPath)
{
	if(_fontPath != fontPath)
	{
		_fontPath = fontPath;
		loadFont();
		needToUpdateTex = true;
	}
}

void Text::setFontSize(int fontSize)
{
	if(_fontSize != fontSize)
	{
		_fontSize = fontSize;
		TTF_SetFontSize(ttfFont, (int)((float)_fontSize * _targetScale) * _quality);
		needToUpdateTex = true;
	}
}

void Text::setText(const std::string& text)
{
	if(_text != text)
	{
		_text = text;
		needToUpdateTex = true;
	}
}

void Text::updateTex()
{
	// delete all lines (textures)
	for (auto& tex : linesTex)
		glDeleteTextures(1, &tex.texID);

	linesTex.clear();

	if (ttfFont == nullptr || _text.empty()) return;
	width = 0;
	height = 0;
	linesCount = 0;

	float yAdd = 0;

	// split text by newline symbol
	std::vector textLines = Utils::split(_text, '\n');

	// loop over all lines
	for(auto& line : textLines)
	{
		// add to lines count (used for transform matrix)
		linesCount++;
		// skip empty line
		if(line.empty())
		{
			yAdd += _fontSize;
			continue;
		}
		unsigned int texID;
		glGenTextures(1, &texID);

		glBindTexture(GL_TEXTURE_2D, texID);
		Texture::curTex = texID;
		
		// render ttfFont with text of the current line in UTF8 format
		initial = TTF_RenderUTF8_Blended(ttfFont, line.c_str(), { 255,255,255,255 });

		// uhhh yea i dont remember why but i think this is needed.
		intermediary = SDL_CreateRGBSurface(0, initial->w, initial->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		if ((float)initial->w >= width)
			width = (float)initial->w;

		SDL_BlitSurface(initial, nullptr, intermediary, nullptr);

		// write pixels data into opengl texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, initial->w, initial->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// add line (texture) to vector
		linesTex.push_back(TexData{ texID, yAdd / _targetScale / (float)_quality, (float)initial->w, (float)initial->h });

		yAdd += (float)initial->h;

		// free shit
		SDL_FreeSurface(initial);
		SDL_FreeSurface(intermediary);
		initial = nullptr;
		intermediary = nullptr;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	Texture::curTex = 0;
	height = yAdd;
}
