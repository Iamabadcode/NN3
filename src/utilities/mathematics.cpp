#include <random>

#include "util.h"


float math::random(vec2 range)
{
	static std::random_device random_device;
	static std::mt19937 rng(random_device());
	static std::uniform_real_distribution<float> dist(range.x, range.y);
	return dist(rng);
}

float math::random_int(vec2i range)
{
	static std::random_device random_device;
	static std::mt19937 rng(random_device());
	static std::uniform_int_distribution<int> dist(range.x, range.y);
	return dist(rng);
}