#pragma once

#include "TEngine.h"
#include "Keys.h"

namespace TEngine
{
	class GameState;
	class Input
	{
	private:
		inline static struct
		{
			bool curKeys[GLFW_KEY_LAST];
			bool curButtons[GLFW_MOUSE_BUTTON_LAST];
			
			bool lastKeys[GLFW_KEY_LAST];
			bool lastButtons[GLFW_MOUSE_BUTTON_LAST];
		} _states;

		inline static float _mouseWheelDelta = 0.f;

		static void init();
		static void keyCallback(Keys key, int scancode, int action, int mods);
		static void mouseButtonCallback(int button, int action, int mods);
		static void scrollCallback(double xOff, double yOff);

		friend class MainGame;
	public:
		// sets prevState to curState
		static void updateStates();

		static float getMouseWheelDelta();

		static bool keyDown(Keys key);
		static bool keyUp(Keys key);
		static bool keyJustPressed(Keys key);
		static bool keyJustReleased(Keys key);

		static bool mouseButtonDown(int button);
		static bool mouseButtonUp(int button);
		static bool mouseButtonJustPressed(int button);
		static bool mouseButtonJustReleased(int button);

		static float getMousePosX(GameState* state = nullptr);
		static float getMousePosY(GameState* state = nullptr);
		static glm::vec2 getMousePos(GameState* state = nullptr);
	};
}
