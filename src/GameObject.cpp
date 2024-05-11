#include "../include/tengine/GameObject.h"
#include "../include/tengine/Utils.h"
#include "../include/tengine/MainGame.h"

glm::vec2 TEngine::GameObject::parallaxPos(const glm::vec2& position)
{
	return glm::vec2{ ((state->getLeft() + state->getRight()) * 0.5f - position.x) * -parallaxX, ((state->getBottom() + state->getTop()) * 0.5f - position.y) * -parallaxY } + position;
}
glm::vec2 TEngine::GameObject::parallaxPos()
{
	return parallaxPos(position);
}

TEngine::GameObject::GameObject(const GameObject& other)
{
	_zOrder = other._zOrder;
	parallaxX = other.parallaxX;
	parallaxY = other.parallaxY;
	position = other.position;
	angle = other.angle;
	scale = other.scale;
	visible = other.visible;
	active = other.active;
	state = other.state;
	blending = other.blending;
}

TEngine::GameObject::GameObject(GameObject&& other) noexcept
{
	_zOrder = other._zOrder;
	parallaxX = other.parallaxX;
	parallaxY = other.parallaxY;
	position = other.position;
	angle = other.angle;
	scale = other.scale;
	visible = other.visible;
	active = other.active;
	state = other.state;
	blending = other.blending;

	other._zOrder = -INT_MAX;
	other.parallaxX = 0;
	other.parallaxY = 0;
	other.position = glm::vec2(0, 0);
	other.angle = 0.0f;
	other.scale = glm::vec2(1, 1);
	other.visible = true;
	other.active = true;
	other.state = nullptr;
	other.blending = BlendMode::Normal;
}

TEngine::GameObject& TEngine::GameObject::operator=(const GameObject& other)
{
	if (this != &other)
	{
		_zOrder = other._zOrder;
		parallaxX = other.parallaxX;
		parallaxY = other.parallaxY;
		position = other.position;
		angle = other.angle;
		scale = other.scale;
		visible = other.visible;
		active = other.active;
		state = other.state;
		blending = other.blending;
	}
	return *this;
}

TEngine::GameObject& TEngine::GameObject::operator=(GameObject&& other) noexcept
{
	if (this != &other)
	{
		_zOrder = other._zOrder;
		parallaxX = other.parallaxX;
		parallaxY = other.parallaxY;
		position = other.position;
		angle = other.angle;
		scale = other.scale;
		visible = other.visible;
		active = other.active;
		state = other.state;
		blending = other.blending;

		other._zOrder = -INT_MAX;
		other.parallaxX = 0;
		other.parallaxY = 0;
		other.position = glm::vec2(0, 0);
		other.angle = 0.0f;
		other.scale = glm::vec2(1, 1);
		other.visible = true;
		other.active = true;
		other.state = nullptr;
		other.blending = BlendMode::Normal;
	}
	return *this;
}


TEngine::GameObject::GameObject() = default;

TEngine::GameObject::GameObject(float x, float y)
{
	setPos(x, y);
}

float TEngine::GameObject::getAngle() const
{
	return angle;
}

glm::vec2 TEngine::GameObject::getPos() const
{
	return position;
}

glm::vec2 TEngine::GameObject::getScale() const
{
	return scale;
}

float TEngine::GameObject::getScaleF() const
{
	return glm::length(scale);
}

float TEngine::GameObject::getX() const
{
	return position.x;
}

float TEngine::GameObject::getY() const
{
	return position.y;
}

int TEngine::GameObject::getZOrder() const
{
	return _zOrder;
}

void TEngine::GameObject::setAngle(float angle)
{
	this->angle = angle;
}

void TEngine::GameObject::setPos(float x, float y)
{
	position.x = x;
	position.y = y;
}

void TEngine::GameObject::setPos(float d)
{
	position.x = d;
	position.y = d;
}

void TEngine::GameObject::setPos(const glm::vec2& pos)
{
	position = pos;
}

void TEngine::GameObject::setScale(float s)
{
	scale.x = s;
	scale.y = s;
}

void TEngine::GameObject::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
}

void TEngine::GameObject::setScale(const glm::vec2& scale)
{
	this->scale = scale;
}

void TEngine::GameObject::setX(float x)
{
	position.x = x;
}

void TEngine::GameObject::setY(float y)
{
	position.y = y;
}

void TEngine::GameObject::setZOrder(int zOrder)
{
	if (_zOrder == zOrder) return;
	_zOrder = zOrder;

	state->updateOrdering();
}

void TEngine::GameObject::start()
{
	
}

void TEngine::GameObject::update(double deltaTime)
{
	if (!state) state = MainGame::getInstance()->curSmthState;
}

void TEngine::GameObject::render(double deltaTime)
{
	if (!state) state = MainGame::getInstance()->curSmthState;

	glBlendEquation(GL_ADD);

	switch (blending)
	{
		case BlendMode::Normal:
		{
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		} break;
		case BlendMode::Additive:
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		} break;
		case BlendMode::Multiply:
		{
			glBlendFuncSeparate(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE);
		} break;
		case BlendMode::Invert:
		{
			glBlendFuncSeparate(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_ONE, GL_ZERO);
		} break;
		default: // same as Normal
		{
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		} break;
	}
}

void TEngine::GameObject::destroy()
{
	visible = false;
	active = false;
}

void TEngine::GameObject::setParallax(float x, float y)
{
	parallaxX = x;
	parallaxY = y;
}

void TEngine::GameObject::setParallax(float xy)
{
	parallaxX = xy;
	parallaxY = xy;
}

TEngine::GameObject::~GameObject()
{
}
