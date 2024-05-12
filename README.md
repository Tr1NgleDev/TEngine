# TEngine
> The worst C++ 2D OpenGL "Game Engine/Framework" **ever**. Full of bad code that you should **never use**!!!

it's x64 windows vs2022 only btw. atleast currently.

## Used Libraries (i hope it's fine to have all of them in `include` directory in this repo):
- [Un4seen BASS audio library](https://www.un4seen.com/) - used for Audio ofc.
- [FFmpeg](https://ffmpeg.org/) - used for Video ofc.
- [glew](https://github.com/nigels-com/glew) - da opengl headers
- [glfw](https://www.glfw.org/) - da window/input lib
- [glm](https://github.com/g-truc/glm) - da funny opengl maths
- [SDL2 and SDL2_ttf](https://github.com/libsdl-org) - text renderingng. might also switch to its window and input later instead of glfw because multi-threading but def not now.
- [nlohmann::json](https://github.com/nlohmann/json) - nlohmann::json
- [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) - loading textures

## How tf do i use this?
You don't!!

ok but seriously tho

- Clone this repo to somewhere and build it with VS2022 or just download the release (if there is one) and put that somewhere idfk you choose.
- Create a new VS2022 C++ Empty Project and create `main.cpp` there
- Go to Project Properties and do these things listed next:
    - Make sure your Configuration is "All Configurations" and Platform is "x64"
    - In "General" set "C++ Language Standard" to `/std:c++20`
    - In "Advanced" make sure you have "Character Set" set to `Multi-Byte`
    - For easier Debugging, in "Debugging" set "Working Directory" to `$(TargetDir)`
    - In "C/C++ > General" in "Additional Include Directories" add path to TEngine's `include` directory.
    - In "Linker > Input" in "Additional Dependencies" add path to your `tengine.lib` that you compiled/downloaded.
    - In "Linker > System" set "SubSystem" to `Windows`
    - In "Build Events > Post-Build Event" add:
    ```bat
    xcopy "YOUR TENGINE PATH WITH FUNNY .DLLS AND THE .LIB AND ASSETS\*.dll" $(TargetDir) /y /b /q /c
    xcopy "YOUR TENGINE PATH WITH FUNNY .DLLS AND THE .LIB AND ASSETS\assets" $(TargetDir)assets /y /b /q /c /s /i
    ``` 
    - (you can also copy the last engine assets line to make it copy your own assets.)
- Go to your `main.cpp` and paste all this weird code in:
```cpp
#include <tengine/TEngine.h>

using namespace TEngine;

int main()
{
	//Console::init(); // do that if you want console
	//Console::printLine("oh hi i can do this. here is a number:", 10); // funny printing
	//Console::printLine(CMode(YELLOW, BRIGHT), "and colors too!", CMode(CYAN, BLINKING), " how cool is that?"); // more funny printing

    // game width, game height, window width, window height, fullscreen, title
	MainGame game = MainGame(1600, 900, 1280, 720, false, "your window title here");
	// target fps, lambda function that executes on load
    game.start(120.0, []
		{
			MainGame::getInstance()->setVSync(false); // just do this ok. it's better this way.
		});
    return 0;
}

// if your subsystem is set to WINDOWS, which it should be.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return main();
}
```
- Make sure you are doing stuff in Release x64
- At this point you have got a window running at 120 fps! (wow!)
- Now comes the fun part, actually making a game!
- Create a `.h` file with whatever class name you want. For example: `MainState.h`. And put all this weird code in:
```cpp
#pragma once // this would be there by default iirc

#include <tengine/TEngine.h>

using namespace TEngine;

class MainState : public GameState
{
public:
	void start() override;
	void update(double dt) override;
};
```
- Create a `.cpp` file with the same name. For example: `MainState.cpp`. And put all this weird code in:
```cpp
#include "MainState.h"

void MainState::start()
{
	GameState::start();
}

void MainState::update(double dt)
{
	GameState::update(dt);
}
```
- And now, in the "on load" lambda function add this:
```cpp
// make sure you have your "MainState.h" included at the top of the main.cpp
MainGame::getInstance()->loadState(new MainState());
```
- Cool! Now you have got an update function (which is called every frame) and a start function (which is called when the "State" gets loaded). "What do i do next?" you may ask. Well. Here is some more example code:
```cpp
// in MainState::start() (make sure to do your stuff after calling the base `GameState::start()`!)
// ...
Sprite* spr = new Sprite(1600 / 2, 900 / 2); // the middle of the screen with camera at the default pos
spr->makeGraphic(100, 100, Color::White()); // make a 100x100 pixels/units white square
spr->offset = {0.5f, 0.5f}; // offset the sprite's origin to be at its center
spr->angle = 45; // rotate the sprite 45 degrees
add(spr); // add sprite to the state
// ...

// in MainState::update(double) (make sure to do your stuff after calling the base `GameState::update(double)`!)
// ...
if (Input::keyDown(Keys::A))
	cam.x -= 200. * dt;
if (Input::keyDown(Keys::D))
	cam.x += 200. * dt;
if (Input::keyDown(Keys::W))
	cam.y -= 200. * dt;
if (Input::keyDown(Keys::S))
	cam.y += 200. * dt;
// ...
```
- Go ahead and run this yourself.

What you do next with all of this is up to you. Go experiment. Look at headers for stuff and try doing stuff. It isn't as hard as it may seem, since there isn't much to look at really.


I probably won't be merging any pull requests or reading any issues. I don't really care lol. It's just a silly little thing i wrote that i use for my own purposes that some other people wanted me to upload to github for no apparent reason.

When you build the engine, all its files that you really need to use (the dlls, the .lib and the assets, except for the includes) are in `x64/Release/tengine` (well, if you build it in x64 Release then yea)