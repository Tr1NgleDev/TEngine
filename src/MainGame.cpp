#include "../include/tengine/MainGame.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/tengine/Audio.h"
#include "../include/tengine/Tween.h"
#include "../include/tengine/Text.h"
#include "../include/tengine/Gradient.h"

#include "../include/tengine/RawInput.h"

void TEngine::MainGame::errorCallback(int error, const char* description)
{
	Console::print(CMode(RED, BRIGHT), std::format("GLFW Error: {}: {}\n", error, description));
}

TEngine::MainGame::MainGame(int gameW, int gameH, int windowW, int windowH, bool fullscreen, const std::string& title)
{
	_instance = this;

#ifdef _WIN32
	HANDLE curThread = GetCurrentThread();
	SetThreadPriority(curThread, 2);
#endif

	if (!glfwInit())
	{
		Console::print(CMode(RED, BRIGHT), "TEngine: Couldn't initialize GLFW!\n");
		return;
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);

	_glfwWindow = glfwCreateWindow(windowW, windowH, title.c_str(), NULL, NULL);
	if (!_glfwWindow)
	{
		Console::print(CMode(RED, BRIGHT), "TEngine: Couldn't initialize GLFW Window!\n");
		glfwTerminate();
		return;
	}

	Audio::init();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) Console::print(CMode(RED, BRIGHT), "TEngine: Couldn't initialize SDL! (SDL_ttf will fail next too. meaning no text *vineboom*)\n");
	if (TTF_Init() != 0) Console::print(CMode(RED, BRIGHT), "TEngine: Couldn't initialize SDL_ttf!\n");

	glm::ivec2 size = getSize();
	_prevWindowedW = size.x;
	_prevWindowedH = size.y;

	if (fullscreen)
		setWindowedFullscreen();

	glfwMakeContextCurrent(_glfwWindow);
	glfwShowWindow(_glfwWindow);

	glewExperimental = 1;

	setVSync(true);

	this->gameWidth = gameW;
	this->gameHeight = gameH;
}

TEngine::MainGame::~MainGame()
{
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}

void TEngine::MainGame::start(double fps, const std::function<void()>& OnLoad)
{
	if (glewInit())
	{
		Console::print(CMode(RED, BRIGHT), "TEngine: Couldn't initialize GLEW!\n");
		glfwDestroyWindow(_glfwWindow);
		glfwTerminate();
		return;
	}

	targetDeltaTime = 1.0 / fps;

	aOnLoad.add(OnLoad);

	init();

	aResize(getWidth(), getHeight());

	double lastTime = 0.0;
	double dt = 0.0;

	while (true)
	{
		double curTime = glfwGetTime();
		dt = curTime - lastTime;
		if(dt >= targetDeltaTime)
		{
			lastTime = curTime;
			glfwPollEvents();
			_deltaTime = std::min(dt, 0.1);
			frameUpdate(_deltaTime, dt);

			Input::updateStates();
		}

		if (glfwWindowShouldClose(_glfwWindow))
		{
			closed();
			break;
		}
	}
}


void TEngine::MainGame::init() const
{
	glfwSetFramebufferSizeCallback(_glfwWindow, resizedWindow);
	glfwSetKeyCallback(_glfwWindow, keyCallback);
	glfwSetMouseButtonCallback(_glfwWindow, mouseButtonCallback);
	glfwSetScrollCallback(_glfwWindow, scrollCallback);

	Input::init();
	Shader::load(RenderTexture::vertPath, RenderTexture::fragPath, RenderTexture::shaderName);
	Shader::load(Sprite::vertPath, Sprite::fragPath, Sprite::shaderName);
	Shader::load(AnimatedSprite::vertPath, AnimatedSprite::fragPath, AnimatedSprite::shaderName);
	Shader::load(Gradient::vertPath, Gradient::fragPath, Gradient::shaderName);
	Sprite::init();

	aOnLoad();

	glClearColor(0, 0, 0, 1);

	glfwSetInputMode(_glfwWindow, GLFW_STICKY_KEYS, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_MULTISAMPLE);
	glBlendEquation(GL_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void TEngine::MainGame::frameUpdate(double deltaTime, double unclampedDT)
{
	_time += unclampedDT;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, backTransparency);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (!MainGame::_instance->switchingStates)
		if (MainGame::_instance->curState)
		{
			MainGame::_instance->curUpdateState = MainGame::_instance->curState;
			MainGame::_instance->curSmthState = MainGame::_instance->curState;
			if (!MainGame::_instance->curState->transOut)
				MainGame::_instance->curState->update(MainGame::_instance->_deltaTime);
		}
	if (!MainGame::_instance->switchingOverlayStates)
		if (MainGame::_instance->curOverlayState)
		{
			MainGame::_instance->curUpdateState = MainGame::_instance->curOverlayState;
			MainGame::_instance->curSmthState = MainGame::_instance->curOverlayState;
			if (!MainGame::_instance->curOverlayState->transOut)
				MainGame::_instance->curOverlayState->update(MainGame::_instance->_deltaTime);
		}
	
	// render
	if (curState)
	{
		curSmthState = curState;
		if (curState->changedData)
		{
			curState->prevChangedData = true;
			curState->changedData = false;
			const float invZoom = 1.f / curState->getZoom();
			const float w = (float)curState->w * curState->targetScale;
			const float h = (float)curState->h * curState->targetScale;

			const float x = curState->cam.x * curState->targetScale - w * 0.5f * invZoom + w * 0.5f;
			const float y = curState->cam.y * curState->targetScale - h * 0.5f * invZoom + h * 0.5f;

			const float centerX = x + w * invZoom * 0.5f;
			const float centerY = y + h * invZoom * 0.5f;

			glm::mat4 viewMat = glm::mat4(1.0);
			Utils::translate(viewMat, -centerX, -centerY);
			Utils::rotate(viewMat, glm::radians(curState->cam.angle));
			Utils::translate(viewMat, centerX, centerY);

			const glm::mat4 projMat = glm::ortho(x, x + w * invZoom, y + h * invZoom, y, -1.f, 1.f);

			curState->projMat = projMat;
			curState->viewMat = viewMat;
		}
		curRenderState = curState;

		curState->renderTex.renderBegin(0, 0, 0, curState->backTransparency);
		glEnable(GL_MULTISAMPLE);
		//glViewport(0, 0, (int)((float)curState->renderTex.w * curState->renderTex.getResScale()), (int)((float)curState->renderTex.h * curState->renderTex.getResScale()));
		curState->render(unclampedDT);
		glViewport((int)curState->offsetX, (int)curState->offsetY, (int)((float)curState->w * curState->targetScale), (int)((float)curState->h * curState->targetScale));
		curState->renderTex.renderEnd(true);
		if (curState->transOut && curState->trans->color.a >= 1.f)
		{
			curState->transOut = false;
			curState->finishedTransOut();
		}
	}
	if (curOverlayState)
	{
		curSmthState = curOverlayState;
		if (curOverlayState->changedData)
		{
			curOverlayState->prevChangedData = true;
			curOverlayState->changedData = false;
			const float invZoom = 1.f / curOverlayState->getZoom();
			const float w = (float)curOverlayState->w * curOverlayState->targetScale;
			const float h = (float)curOverlayState->h * curOverlayState->targetScale;

			const float x = curOverlayState->cam.x * curOverlayState->targetScale - w * 0.5f * invZoom + w * 0.5f;
			const float y = curOverlayState->cam.y * curOverlayState->targetScale - h * 0.5f * invZoom + h * 0.5f;

			const float centerX = x + w * invZoom * 0.5f;
			const float centerY = y + h * invZoom * 0.5f;

			glm::mat4 viewMat = glm::mat4(1.0);
			Utils::translate(viewMat, -centerX, -centerY);
			Utils::rotate(viewMat, glm::radians(curOverlayState->cam.angle));
			Utils::translate(viewMat, centerX, centerY);

			const glm::mat4 projMat = glm::ortho(x, x + w * invZoom, y + h * invZoom, y, -1.f, 1.f);

			curOverlayState->projMat = projMat;
			curOverlayState->viewMat = viewMat;
		}
		curRenderState = curOverlayState;

		curOverlayState->renderTex.renderBegin(0, 0, 0, 0);
		glEnable(GL_MULTISAMPLE);
		//glViewport(0, 0, (int)((float)curOverlayState->renderTex.w * curOverlayState->renderTex.getResScale()), (int)((float)curOverlayState->renderTex.h * curOverlayState->renderTex.getResScale()));
		curOverlayState->render(unclampedDT);
		glViewport((int)curOverlayState->offsetX, (int)curOverlayState->offsetY, (int)((float)curOverlayState->w * curOverlayState->targetScale), (int)((float)curOverlayState->h * curOverlayState->targetScale));
		curOverlayState->renderTex.renderEnd(true);

		if (curOverlayState->transOut && curOverlayState->trans->color.a >= 1.f)
		{
			curOverlayState->transOut = false;
			curOverlayState->finishedTransOut();
		}
	}

	glfwSwapBuffers(_glfwWindow);
}

TEngine::MainGame* TEngine::MainGame::getInstance()
{
	return _instance;
}

double TEngine::MainGame::getDeltaTime() const
{
	return _deltaTime;
}

double TEngine::MainGame::getTargetDeltaTime() const
{
	return targetDeltaTime;
}

double TEngine::MainGame::getTime() const
{
	return _time;
}

GLFWwindow* TEngine::MainGame::getWindow() const
{
	return _glfwWindow;
}

int TEngine::MainGame::getWidth() const
{
	return getSize().x;
}

int TEngine::MainGame::getHeight() const
{
	return getSize().y;
}

glm::ivec2 TEngine::MainGame::getSize() const
{
	int w, h;
	glfwGetWindowSize(_glfwWindow, &w, &h);
	return { w, h };
}

void TEngine::MainGame::setWidth(int w) const
{
	setSize({ w, getHeight() });
}

void TEngine::MainGame::setHeight(int h) const
{
	setSize({ getWidth(), h });
}

void TEngine::MainGame::setSize(const glm::ivec2& size) const
{
	glfwSetWindowSize(_glfwWindow, size.x, size.y);
}

glm::vec2 TEngine::MainGame::getMousePosWindow() const
{
	double x, y;
	glfwGetCursorPos(_glfwWindow, &x, &y);
	return { static_cast<float>(x),static_cast<float>(y) };
}

void TEngine::MainGame::resizedWindow(GLFWwindow* window, int width, int height)
{
	MainGame::getInstance()->aResize(width, height);
}

void TEngine::MainGame::setFullscreen()
{
	glfwSetWindowAttrib(_glfwWindow, GLFW_DECORATED, GLFW_FALSE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	glfwGetWindowSize(_glfwWindow, &_prevWindowedW, &_prevWindowedH);
	glfwGetWindowPos(_glfwWindow, &_prevWindowedX, &_prevWindowedY);

	glfwSetWindowSize(_glfwWindow, mode->width, mode->height);
	glfwSetWindowMonitor(_glfwWindow, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);

	resizedWindow(_glfwWindow, mode->width, mode->height);
}

void TEngine::MainGame::setWindowed()
{
	glfwSetWindowAttrib(_glfwWindow, GLFW_DECORATED, GLFW_TRUE);

	glfwSetWindowMonitor(_glfwWindow, nullptr, _prevWindowedX, _prevWindowedY, _prevWindowedW, _prevWindowedH, GLFW_DONT_CARE);

	setSize({ _prevWindowedW, _prevWindowedH });
	setPos({ _prevWindowedX, _prevWindowedY });

	resizedWindow(_glfwWindow, _prevWindowedW, _prevWindowedH);
}

void TEngine::MainGame::setWindowedFullscreen()
{
	glfwSetWindowAttrib(_glfwWindow, GLFW_DECORATED, GLFW_FALSE);

	glfwGetWindowSize(_glfwWindow, &_prevWindowedW, &_prevWindowedH);
	glfwGetWindowPos(_glfwWindow, &_prevWindowedX, &_prevWindowedY);

	glfwSetWindowMonitor(_glfwWindow, nullptr, _prevWindowedX, _prevWindowedY, _prevWindowedW, _prevWindowedH, GLFW_DONT_CARE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	glfwSetWindowSize(_glfwWindow, mode->width, mode->height);
	glfwSetWindowPos(_glfwWindow, 0, 0);

	resizedWindow(_glfwWindow, mode->width, mode->height);
}

glm::ivec2 TEngine::MainGame::getPos() const
{
	int x, y;
	glfwGetWindowPos(_glfwWindow, &x, &y);
	return { x, y };
}

void TEngine::MainGame::setPos(const glm::ivec2& pos) const
{
	glfwSetWindowPos(_glfwWindow, pos.x, pos.y);
}

bool TEngine::MainGame::getVSync() const
{
	return _vsync;
}

void TEngine::MainGame::setVSync(bool vsync)
{
	_vsync = vsync;
	glfwSwapInterval(_vsync ? 1 : 0);
}

bool TEngine::MainGame::isWindowed() const
{
	auto v = glfwGetWindowAttrib(_glfwWindow, GLFW_DECORATED);
	auto m = glfwGetWindowMonitor(_glfwWindow);
	return v == GLFW_TRUE && m == nullptr;
}

void TEngine::MainGame::closed()
{
	//TweenManager::stopAll();
	if (RawInput::initialized)
	{
		if(RawInput::riHWND != nullptr)
			CloseWindow(RawInput::riHWND);

	}
	unloadState();
	unloadOverlayState();
	Shader::disposeShaders();
	for (auto& tex : Texture::loadedTextures)
	{
		glDeleteTextures(1, &tex.second->id);
		delete tex.second;
	}
	Texture::loadedTextures.clear();
	Audio::destroy();

	TTF_Quit();
	SDL_Quit();
	
	glBindVertexArray(Sprite::VAO);
	glDeleteVertexArrays(1, &Sprite::VAO);
	glDeleteBuffers(1, &Sprite::VBO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TEngine::MainGame::loadState(GameState* s)
{
	switchingStates = true;
	nextState = s;
	auto fin = []
		{
			if (!MainGame::getInstance()->switchingStates) return;
			MainGame::getInstance()->switchingStates = false;
			MainGame::getInstance()->unloadState();
			MainGame::getInstance()->curState = MainGame::getInstance()->nextState;
			MainGame::getInstance()->curStartState = MainGame::getInstance()->nextState;
			MainGame::getInstance()->curSmthState = MainGame::getInstance()->nextState;
		
			MainGame::getInstance()->curState->start();
			MainGame::getInstance()->curState->resized(MainGame::getInstance()->getWidth(), MainGame::getInstance()->getHeight());
		};
	if (curState && !curState->transOut)
	{
		curState->transOut = true;
		curState->transStart = curState->renderTime;
		curState->finishedTransOut.add(fin);
	}
	else if (!curState)
		fin();
}

void TEngine::MainGame::loadOverlayState(GameState* s)
{
	switchingOverlayStates = true;
	nextOverlayState = s;
	auto fin = []
		{
			if (!MainGame::getInstance()->switchingOverlayStates) return;
			MainGame::getInstance()->switchingOverlayStates = false;
			MainGame::getInstance()->unloadOverlayState();
			MainGame::getInstance()->curOverlayState = MainGame::getInstance()->nextOverlayState;
			MainGame::getInstance()->curStartState = MainGame::getInstance()->nextOverlayState;
			MainGame::getInstance()->curSmthState = MainGame::getInstance()->nextOverlayState;
			MainGame::getInstance()->curOverlayState->start();
			MainGame::getInstance()->curOverlayState->resized(MainGame::getInstance()->getWidth(), MainGame::getInstance()->getHeight());
		};
	if (curOverlayState && !curOverlayState->transOut)
	{
		curOverlayState->transOut = true;
		curOverlayState->transStart = curOverlayState->renderTime;
		curOverlayState->finishedTransOut.add(fin);
	}
	else if (!curOverlayState)
		fin();
}

void TEngine::MainGame::unloadState()
{
	if (curState)
	{
		curState->exit();
		delete curState;
		curState = nullptr;
	}
}

void TEngine::MainGame::unloadOverlayState()
{
	if (curOverlayState)
	{
		curOverlayState->exit();
		delete curOverlayState;
		curOverlayState = nullptr;
	}
}

void TEngine::MainGame::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!getInstance()->isFocused()) return;
	MainGame::getInstance()->aKeyCallback((Keys)key, scancode, action, mods);
}

void TEngine::MainGame::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (!getInstance()->isFocused()) return;
	MainGame::getInstance()->aMouseButtonCallback(button, action, mods);
}

void TEngine::MainGame::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (!getInstance()->isFocused()) return;
	MainGame::getInstance()->aScrollCallback(xoffset, yoffset);
}

bool TEngine::MainGame::isFocused() const
{
	return glfwGetWindowAttrib(_glfwWindow, GLFW_FOCUSED);
}

HWND TEngine::MainGame::getHWND() const
{
	return glfwGetWin32Window(_glfwWindow);
}
