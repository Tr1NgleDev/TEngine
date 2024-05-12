#include "../include/tengine/RawInput.h"

using namespace TEngine;

HWND RawInput::riHWND = nullptr;

void RawInput::init()
{
	initialized = true;
	rawInputThread = std::thread(rawInput);
}

void RawInput::rawInput()
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.lpszClassName = "TEngine::RawInput";

	RegisterClass(&wc);
	riHWND = CreateWindow("TEngine::RawInput", "TEngine::RawInputWnd", 0, 0, 0, 0, 0, HWND_MESSAGE, 0, wc.hInstance, 0);
	if (!riHWND)
	{
		const DWORD err = GetLastError();
		Console::printLine("TEngine::RawInput: Failed to create Raw Input HWND. Error Code: ", err);
		return;
	}

	RAWINPUTDEVICE dev[2];

	// keyboard
	dev[0].usUsagePage = 0x01;        
	dev[0].usUsage = 0x06;            
	dev[0].dwFlags = RIDEV_INPUTSINK; 
	dev[0].hwndTarget = riHWND;

	// mouse
	dev[1].usUsagePage = 0x01;
	dev[1].usUsage = 0x02;            
	dev[1].dwFlags = RIDEV_INPUTSINK;
	dev[1].hwndTarget = riHWND;

	if (!RegisterRawInputDevices(dev, 2, sizeof(dev[0]))) 
	{
		Console::printLine("TEngine::RawInput: Failed to register the Raw Input Devices.");
		return;
	}

	MSG msg;
	while (GetMessage(&msg, riHWND, 0, 0))
		DispatchMessage(&msg);
}

LRESULT CALLBACK RawInput::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
		case WM_INPUT: 
		{
			UINT dwSize;
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

			auto lpb = std::unique_ptr<BYTE[]>(new BYTE[dwSize]);
			if (!lpb)
				return 0;
			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb.get(), &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
				Console::printLine("TEngine::RawInput: GetRawInput() does not return correct size.");

			RAWINPUT* raw = (RAWINPUT*)lpb.get();
			switch (raw->header.dwType) 
			{
				case RIM_TYPEKEYBOARD: 
				{
					Keys vkey = (Keys)raw->data.keyboard.VKey;
					bool state = !(bool)(raw->data.keyboard.Flags & RI_KEY_BREAK);

					if (heldKeys.contains(vkey))
					{
						if (state)
							break;
						else
							heldKeys.erase(vkey);
					}
					if (state)
						heldKeys.insert(vkey);

					onKeyInput(vkey, glfwGetTime(), state);
				} break;
				case RIM_TYPEMOUSE: 
				{
					// button input
					{
						USHORT flags = raw->data.mouse.usButtonFlags;
						bool state = false;
						int button = GLFW_MOUSE_BUTTON_LEFT;

						if (flags & RI_MOUSE_BUTTON_1_DOWN) { button = GLFW_MOUSE_BUTTON_LEFT; state = true; }
						else if (flags & RI_MOUSE_BUTTON_1_UP) { button = GLFW_MOUSE_BUTTON_LEFT; state = false; }
						else if (flags & RI_MOUSE_BUTTON_2_DOWN) { button = GLFW_MOUSE_BUTTON_RIGHT; state = true; }
						else if (flags & RI_MOUSE_BUTTON_2_UP) { button = GLFW_MOUSE_BUTTON_RIGHT; state = false; }
						else if (flags & RI_MOUSE_BUTTON_3_DOWN) { button = GLFW_MOUSE_BUTTON_MIDDLE; state = true; }
						else if (flags & RI_MOUSE_BUTTON_3_UP) { button = GLFW_MOUSE_BUTTON_MIDDLE; state = false; }
						else break;

						if (mouseBtnStates[button] != state)
						{
							mouseBtnStates[button] = state;
							onButtonInput(button, glfwGetTime(), state);
						}
					}
					// movement
					/*
					{
						if (raw->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
						{
							RECT rect;
							if (raw->data.mouse.usFlags & MOUSE_VIRTUAL_DESKTOP)
							{
								rect.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
								rect.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
								rect.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
								rect.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
							}
							else
							{
								rect.left = 0;
								rect.top = 0;
								rect.right = GetSystemMetrics(SM_CXSCREEN);
								rect.bottom = GetSystemMetrics(SM_CYSCREEN);
							}

							int absoluteX = MulDiv(raw->data.mouse.lLastX, rect.right, 65535) + rect.left;
							int absoluteY = MulDiv(raw->data.mouse.lLastY, rect.bottom, 65535) + rect.top;
						}
						else if (raw->data.mouse.lLastX != 0 || raw->data.mouse.lLastY != 0)
						{
							int relativeX = raw->data.mouse.lLastX;
							int relativeY = raw->data.mouse.lLastY;
						}
					}*/
				} break;
			}
			return 0;
		} break;
		default:
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}
}
