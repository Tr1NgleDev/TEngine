#pragma once

#include "TEngine.h"

#include <thread>

namespace TEngine
{
	class GameState;
	class MainGame
	{
	private:
		inline static MainGame* _instance = nullptr;

		double _deltaTime = 0.001;
		double _time = 0;
		GLFWwindow* _glfwWindow = nullptr;
		int _prevWindowedW = 1, _prevWindowedH = 1, _prevWindowedX = -1, _prevWindowedY = -1;
		bool _vsync = false;
		GameState* nextState;
		GameState* nextOverlayState;

		void init() const;
		void frameUpdate(double deltaTime, double unclampedDT);
		static void errorCallback(int error, const char* description);
		static void resizedWindow(GLFWwindow* window, int width, int height);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		void closed();

	public:
		float backTransparency = 1;
		double targetDeltaTime = 0.001;
		int gameWidth = 0, gameHeight = 0;

		bool switchingStates = false;
		bool switchingOverlayStates = false;

		GameState* curState;
		GameState* curOverlayState;
		GameState* curUpdateState;
		GameState* curRenderState;
		GameState* curStartState;
		GameState* curSmthState;

		Action<void()> aOnLoad;
		Action<void(int width, int height)> aResize;
		Action<void(Keys key, int scancode, int action, int mods)> aKeyCallback;
		Action<void(int button, int action, int mods)> aMouseButtonCallback;
		Action<void(double xOff, double yOff)> aScrollCallback;

		MainGame(int gameW, int gameH, int windowW, int windowH, bool fullscreen, const std::string& title);
		~MainGame();

		void start(double fps, const std::function<void()>& OnLoad = nullptr);

		static MainGame* getInstance();

		double getTime() const;
		double getTargetDeltaTime() const;
		double getDeltaTime() const;
		
		int getWidth() const;
		int getHeight() const;

		void setWidth(int w) const;
		void setHeight(int h) const;

		glm::ivec2 getSize() const;
		void setSize(const glm::ivec2& size) const;

		glm::ivec2 getPos() const;
		void setPos(const glm::ivec2& pos) const;

		glm::vec2 getMousePosWindow() const;

		GLFWwindow* getWindow() const;

		void setFullscreen();
		void setWindowedFullscreen();
		void setWindowed();

		bool getVSync() const;
		void setVSync(bool vsync);

		bool isWindowed() const;

		void loadState(GameState* s);
		void loadOverlayState(GameState* s);
		void unloadState();
		void unloadOverlayState();

		bool isFocused() const;

		HWND getHWND() const;
	};
}