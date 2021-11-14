#pragma once
#include <random>

namespace Utils {
    // @param from Random start
    // @param to Random end
    // @return Random value in range [from, to]
    float RandRange(float from, float to);
	// @param to Random end
	// @return Random value in range [0, to]
	float RandRange(float to);
	float RoundTo(float val, int k);
}