#include "../include/tengine/Input.h"

void TEngine::Input::init()
{
	MainGame::getInstance()->aKeyCallback.add(keyCallback);
	MainGame::getInstance()->aMouseButtonCallback.add(mouseButtonCallback);
	MainGame::getInstance()->aScrollCallback.add(scrollCallback);
}

void TEngine::Input::keyCallback(Keys key, int scancode, int action, int mods)
{
	_states.curKeys[(int)key] = action != GLFW_RELEASE;
}

void TEngine::Input::mouseButtonCallback(int button, int action, int mods)
{
	_states.curButtons[button] = action != GLFW_RELEASE;
}

void TEngine::Input::scrollCallback(double xOff, double yOff)
{
	_mouseWheelDelta = static_cast<float>(yOff);
}

void TEngine::Input::updateStates()
{
	std::memcpy(_states.lastKeys, _states.curKeys, GLFW_KEY_LAST * sizeof(bool));
	std::memcpy(_states.lastButtons, _states.curButtons, GLFW_MOUSE_BUTTON_LAST * sizeof(bool));
}

float TEngine::Input::getMousePosX(GameState* state)
{
	float x = getMousePos(state).x;
	return x;
}

float TEngine::Input::getMousePosY(GameState* state)
{
	float y = getMousePos(state).y;
	return y;
}

glm::vec2 TEngine::Input::getMousePos(GameState* state)
{
	if (state == nullptr)
		state = MainGame::getInstance()->curUpdateState;

	const glm::vec2 mousePosWindow = MainGame::getInstance()->getMousePosWindow();
	float x = mousePosWindow.x;
	float y = mousePosWindow.y;

	x = Utils::remap(x, state->offsetX, static_cast<float>(MainGame::getInstance()->getWidth()) - state->offsetX, 0.f, static_cast<float>(state->w));
	y = Utils::remap(y, state->offsetY, static_cast<float>(MainGame::getInstance()->getHeight()) - state->offsetY, 0.f, static_cast<float>(state->h));

	return { x, y };
}

float TEngine::Input::getMouseWheelDelta()
{
	return _mouseWheelDelta;
}

bool TEngine::Input::keyDown(Keys key)
{
	return _states.curKeys[(int)key] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::keyUp(Keys key)
{
	return !_states.curKeys[(int)key] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::keyJustPressed(Keys key)
{
	return _states.curKeys[(int)key] && !_states.lastKeys[(int)key] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::keyJustReleased(Keys key)
{
	return !_states.curKeys[(int)key] && _states.lastKeys[(int)key] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::mouseButtonDown(int button)
{
	return _states.curButtons[button] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::mouseButtonUp(int button)
{
	return !_states.curButtons[button] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::mouseButtonJustPressed(int button)
{
	return _states.curButtons[button] && !_states.curButtons[button] && MainGame::getInstance()->isFocused();
}

bool TEngine::Input::mouseButtonJustReleased(int button)
{
	return !_states.curButtons[button] && _states.curButtons[button] && MainGame::getInstance()->isFocused();
}
