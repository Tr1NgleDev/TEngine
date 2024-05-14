#include "../include/tengine/Sprite.h"
#include "../include/tengine/Shader.h"
#include "../include/tengine/Texture.h"

TEngine::Sprite::Sprite()
{
	this->color = Color::White();
	// im sorry for doing that but im lazy to check if there is another way
	shader = Shader::get(Sprite::shaderName);
	tex = Texture::get(Color::White());
	setAntialiased(false);
	
}

TEngine::Sprite::Sprite(const Color& color)
{
	this->color = Color::White();
	// im sorry for doing that but im lazy to check if there is another way
	shader = Shader::get(Sprite::shaderName);
	tex = Texture::get(color);
	setAntialiased(false);
	
}

TEngine::Sprite::Sprite(Texture* texture)
{
	this->color = Color::White();
	shader = Shader::get(Sprite::shaderName);
	tex = texture;
	setAntialiased(!MainGame::getInstance()->curSmthState->pixelPerfect);
	
}

TEngine::Sprite::Sprite(float x, float y)
{
	this->color = Color::White();
	this->setPos(x, y);
	// im sorry for doing that but im lazy to check if there is another way
	shader = Shader::get(Sprite::shaderName);
	tex = Texture::get(Color::White()); 
	setAntialiased(false);
	
}

TEngine::Sprite::Sprite(const glm::vec2& pos)
{
	this->color = Color::White();
	this->setPos(pos);
	// im sorry for doing that but im lazy to check if there is another way
	shader = Shader::get(Sprite::shaderName);
	tex = Texture::get(Color::White());
	setAntialiased(false);
	
}

TEngine::Sprite* TEngine::Sprite::createFromTexFile(const std::string& filePath)
{
	return (new Sprite())->loadTex(filePath);
}

void TEngine::Sprite::init()
{
	if (VAO != 0 && VBO != 0) return;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_UNSIGNED_BYTE, GL_FALSE, 4 * sizeof(uint8_t), nullptr); // pos
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, 4 * sizeof(uint8_t), (void*)(2 * sizeof(uint8_t))); // uv
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	instancing = MainGame::getInstance()->instancedRendering;
}

bool TEngine::Sprite::getAntialiased() const
{
	return _antialiased;
}

void TEngine::Sprite::setAntialiased(bool v)
{
	_antialiased = v;
	tex->setAntialiasing(_antialiased);
}

TEngine::Sprite* TEngine::Sprite::loadTex(const std::string& filePath, bool antialiased)
{
	tex = Texture::get(filePath, _antialiased);
	setAntialiased(antialiased);
	return this;
}

TEngine::Sprite* TEngine::Sprite::loadTex(const std::string& filePath)
{
	tex = Texture::get(filePath, _antialiased);
	setAntialiased(!MainGame::getInstance()->curSmthState->pixelPerfect);
	return this;
}

TEngine::Sprite* TEngine::Sprite::makeGraphic(const glm::ivec2& size)
{
	tex = Texture::get(size.x, size.y, Color::White(), _antialiased);
	return this;
}

TEngine::Sprite* TEngine::Sprite::makeGraphic(const glm::ivec2& size, const Color& color)
{
	tex = Texture::get(size.x, size.y, color, _antialiased);
	return this;
}

TEngine::Sprite* TEngine::Sprite::makeGraphic(int w, int h)
{
	tex = Texture::get(w, h, Color::White(), _antialiased);
	return this;
}

TEngine::Sprite* TEngine::Sprite::makeGraphic(int w, int h, const Color& color)
{
	tex = Texture::get(w, h, color, _antialiased);
	return this;
}

void TEngine::Sprite::screenCenter(Axes axes, bool basedOnCamera)
{
	if (axes != Axes::Y)
	{
		if (!basedOnCamera)
			position.x = ((float)state->w / 2.f) - ((float)tex->w * scale.x / 2.f);
		else
			position.x = (state->getLeft() + state->getRight()) / 2.f - ((float)tex->w * scale.x / 2.f);
	}
	if (axes != Axes::X)
	{
		if(!basedOnCamera)
			position.y = ((float)state->h / 2.f) - ((float)tex->h * scale.y / 2.f);
		else
			position.y = (state->getBottom() + state->getTop()) / 2.f - ((float)tex->h * scale.y / 2.f);
	}
}

void TEngine::Sprite::setGraphicSize(int width, int height)
{
	if (width < 0 && height < 0)
		return;

	float newScaleX = (float)width / (float)tex->w;
	float newScaleY = (float)height / (float)tex->h;
	scale = { newScaleX, newScaleY };

	if (width <= 0)
		scale.x = newScaleY;
	else if (height <= 0)
		scale.y = newScaleX;
}

void TEngine::Sprite::render(double deltaTime)
{
	if (instancing != MainGame::getInstance()->instancedRendering)
		init();

	glm::vec2 pos = parallaxPos();
	if (dontRenderOutside)
	{
		const glm::vec2 texSize = tex->getSize();
		glm::vec2 min = pos - offset * texSize * scale - texSize * scale * 2.0f;
		glm::vec2 max = pos + offset * texSize * scale + texSize * scale * 2.0f;
		if (max.x < state->getLeft() && min.x < state->getLeft() ||
			max.x > state->getLeft() && min.x > state->getRight() ||
			max.y < state->getTop() && min.y < state->getTop() ||
			max.y > state->getBottom() && min.y > state->getBottom())
			return;
	}
	
	GameObject::render(deltaTime);
	bindBuffers();
	shader->use();
	
	/*
	if(_updateTransform)
	{
		if (!state->pixelPerfect)
		{
			transform = Utils::createScale((float)tex->w * scale.x, (float)tex->h * scale.y);
			Utils::translate(transform, -offset.x * (float)tex->w * scale.x, -offset.y * (float)tex->h * scale.y);
			Utils::rotate(transform, glm::radians(angle));
			Utils::translate(transform, position.x, position.y);
		}
		else
		{
			transform = Utils::createScale(floorf((float)tex->w * scale.x), floorf((float)tex->h * scale.y));
			Utils::translate(transform, floorf(-offset.x * (float)tex->w * scale.x), floorf(-offset.y * (float)tex->h * scale.y));
			Utils::rotate(transform, glm::radians(angle));
			Utils::translate(transform, floorf(position.x), floorf(position.y));
		}
		Utils::scale(transform, state->targetScale, state->targetScale);
		_updateTransform = false;
	}
	*/

	shader->setUniform("scale", glm::vec2((float)tex->w * scale.x, (float)tex->h * scale.y));
	shader->setUniform("offset", -offset);
	shader->setUniform("position", pos);
	shader->setUniform("angle", glm::radians(angle));
	shader->setUniform("targetScale", state->targetScale);
	shader->setUniform("pixelPerfect", state->pixelPerfect);

	//shader->setUniform("transform", transform, false);
	shader->setUniform("projection", state->projMat, false);
	shader->setUniform("view", state->viewMat, false);
	shader->setUniform("color", color);
	shader->setUniform("time", (float)MainGame::getInstance()->getTime());
	shader->setUniform("flip", glm::vec2{ flipX ? 1.f : 0.f, flipY ? 1.f : 0.f });
	shader->setUniform("bitmap", 0);
	tex->use();
	drawVertices();
}
