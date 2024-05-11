#pragma once

#include <random>
#include "TEngine.h"

namespace TEngine
{
	class Random
	{
		inline static float prevVal;
		inline static int prevValI;
		inline static double prevValD;
	public:
		static int getInt(int min, int max);
		static int getInt(int min, int max, int seed);
		// from -1 to 1
		static float getFloat();
		// from -1 to 1 based on coordinates (good for texture noise)
		static float getFloat(glm::vec2 co);
		static float getFloat(float min, float max);
		static float getFloat(float min, float max, int seed);
		static double getDouble(double min, double max);
		static double getDouble(double min, double max, int seed);
	};
}