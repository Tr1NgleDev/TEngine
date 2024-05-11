#include "../include/tengine/Random.h"

double TEngine::Random::getDouble(double min, double max)
{
	static std::random_device device;
	std::mt19937 generator(device() + (int)(prevValD * 353148.3563136278869) + (int)(prevVal * 35248.356314f) + prevValI);
	std::uniform_real_distribution<double> distribution(min, max);

	return prevValD = distribution(generator);
}

float TEngine::Random::getFloat()
{
	static std::random_device device;
	std::mt19937 generator(device() + (int)(prevValD * 353148.3563136278869) + (int)(prevVal * 35248.356314f) + prevValI);
	std::uniform_real_distribution<float> distribution(-1.f, 1.f);

	return prevVal = distribution(generator);
}

float TEngine::Random::getFloat(float min, float max)
{
	static std::random_device device;
	std::mt19937 generator(device() + (int)(prevValD * 353148.3563136278869) + (int)(prevVal * 35248.356314f) + prevValI);
	std::uniform_real_distribution<float> distribution(min, max);

	return prevVal = distribution(generator);
}

float TEngine::Random::getFloat(glm::vec2 co)
{
	co *= (int)(prevValD * 353148.3563136278869) + (int)(prevVal * 35248.356314f) + prevValI;
	return prevVal = glm::fract(glm::sin(glm::dot(co, { 12.9898f, 78.233f })) * 43758.5453f) * 2.f - 1.f;
}

int TEngine::Random::getInt(int min, int max)
{
	static std::random_device device;
	std::mt19937 generator(device() + (int)(prevValD * 353148.3563136278869) + (int)(prevVal * 35248.356314f) + prevValI);
	std::uniform_int_distribution<int> distribution(min, max);

	return prevValI = distribution(generator);
}

double TEngine::Random::getDouble(double min, double max, int seed)
{
	std::mt19937 generator(seed);
	std::uniform_real_distribution<double> distribution(min, max);

	return prevValD = distribution(generator);
}

float TEngine::Random::getFloat(float min, float max, int seed)
{
	std::mt19937 generator(seed);
	std::uniform_real_distribution<float> distribution(min, max);

	return prevVal = distribution(generator);
}

int TEngine::Random::getInt(int min, int max, int seed)
{
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(min, max);

	return prevValI = distribution(generator);
}
