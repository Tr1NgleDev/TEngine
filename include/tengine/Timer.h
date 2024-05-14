#pragma once

#include "BasicIncludes.h"

namespace TEngine
{
	class GameState;
	class Timer
	{
	public: 
		inline static double globalSpeed = 1.0;
		double time = 0.;
		double duration = 0.;
		int ind = 1;
		int times = 1;
		std::function<void()> callback;
		Timer(GameState* state, double duration, const std::function<void()>& callback, int times = 1);
	};
}
