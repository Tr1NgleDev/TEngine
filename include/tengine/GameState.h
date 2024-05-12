#pragma once

#include "TEngine.h"
#include "RenderTexture.h"

namespace TEngine
{
	class GameObject;
	class Sprite;
	class Timer;
	class Tween;
	class GameState
	{
	private:
		int resizedActionInd = -1;
		std::vector<Timer*> timers;
		std::vector<Tween*> tweens;
		Sprite* trans;
		//std::vector<GameObject*> allObjects;
		struct
		{
			float zoom = 0;
			float x = 0;
			float y = 0;
			float angle = 0;
		} prevCam;
		// prev RenderTexture stuff
		int prevRTW, prevRTH;
		bool changedData = true;
		bool prevChangedData = true;

		bool resort = true;

		void updateTimers(double deltaTime);
		void updateTweens(double deltaTime);

		friend class MainGame;
		friend class Timer;
		friend class Tween;
	public:
		double tweenSpeed = 1.0;
		// doesnt apply to overlay states
		float backTransparency = 1;
		//std::map<int, std::vector<GameObject*>> objects;
		std::vector<GameObject*> objects;
		RenderTexture renderTex;
		int w = 0, h = 0;
		float offsetX = 0, offsetY = 0;
		float targetScale = 1;
		struct
		{
			float zoom = 0;
			float x = 0;
			float y = 0;
			float angle = 0;
		} cam;
		glm::mat4 projMat;
		glm::mat4 viewMat;
		bool pixelPerfect = false;
		double stateTime = 0;
		double renderTime = 0;
		bool transOut = false;
		double transStart = 0;
		Action<void()> finishedTransOut;

		GameState();
		~GameState();
		void resized(int width, int height);
		virtual void start();
		virtual void exit();
		virtual void update(double deltaTime);
		virtual void render(double deltaTime);
		void add(GameObject* obj, int zOrder);
		void add(GameObject* obj);
		void remove(GameObject* obj);
		// returns Y position of the Top side (based on camera)
		float getTop() const;
		// returns Y position of the Bottom side (based on camera)
		float getBottom() const;
		// returns X position of the Left side (based on camera)
		float getLeft() const;
		// returns X position of the Right side (based on camera)
		float getRight() const;
		float getZoom() const;
		void updateOrdering();
	};
}
