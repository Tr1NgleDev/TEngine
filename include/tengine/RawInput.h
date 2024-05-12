#pragma once

#include "TEngine.h"
#include "Keys.h"

namespace TEngine
{
	// This is WINDOWS ONLY and WILL ALWAYS BE!!!
	class RawInput
	{
	private:
		static HWND riHWND;
		inline static bool initialized = false;
		inline static std::thread rawInputThread{};
		static void rawInput();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		inline static std::set<Keys> heldKeys{};
		inline static bool mouseBtnStates[3]{false,false,false};
		friend class MainGame;
	public:
		inline static Action<void(Keys key, double time, bool state)> onKeyInput{};
		inline static Action<void(int button, double time, bool state)> onButtonInput{};
		//inline static Action<void(glm::vec2 pos, double time)> onMouseMoveInput{};
		static void init();
	};
}
