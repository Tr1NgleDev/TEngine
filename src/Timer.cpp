#include "../../include/tengine/Timer.h"
#include "../../include/tengine/GameState.h"

TEngine::Timer::Timer(GameState* state, double duration, const std::function<void()>& callback, int times)
	: duration(duration), callback(callback), times(times)
{
	state->timers.push_back(this);
}
