#include <random>

#include "util.h"


float math::random(vec2 range) noexcept
{
	static std::random_device random_device;
	static std::mt19937 rng(random_device());
	std::uniform_real_distribution<float> dist(range.x, range.y);
	return dist(rng);
}

float math::random_int(vec2i range) noexcept
{
	static std::random_device random_device;
	static std::mt19937 rng(random_device());
	std::uniform_int_distribution<int> dist(range.x, range.y);
	return dist(rng);
}