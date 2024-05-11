#pragma once        

// opengl stuff

#define GLEW_STATIC

#include "../glew/glew.h"

#include "../glfw/glfw3.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "../glfw/glfw3native.h"

#include "BasicIncludes.h"

// IO

#include "IO/File.h"
#include "IO/Directory.h"


// Main

#include "Axes.h"
#include "BlendMode.h"
#include "Keys.h"
#include "Console.h"
#include "Action.h"
#include "Color.h"
#include "Utils.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Texture.h"
#include "MainGame.h"
#include "Input.h"
#include "GameObject.h"
#include "Rect.h"
#include "Sprite.h"
#include "Random.h"
#include "Video.h"
#include "GameState.h"
#include "Audio.h"
#include "Tween.h"
#include "Gradient.h"
#include "Timer.h"
#include "AnimatedSprite.h"

#define SDL_MAIN_HANDLED
#include "Text.h"
#undef main
