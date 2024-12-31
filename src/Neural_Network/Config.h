#pragma once
#include "../utilities/util.h"

//#define Multi_Threading
//#define SIMD

constexpr unsigned int MEMORY_ALIGNEMENT = 32;
constexpr unsigned int MEMORY_CAP = 9999999;

constexpr math::vec2 BIAS_INIT_RANGE = {-1, 1};
constexpr math::vec2 WEIGHT_INIT_RANGE = { -1, 1 };
