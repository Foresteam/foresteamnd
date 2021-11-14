#pragma once
#include <random>

namespace Utils {
    // @param from Random start
    // @param to Random end
    // @return Random value in range [from, to]
    double RandRange(double from, double to);
	// @param to Random end
	// @return Random value in range [0, to]
	double RandRange(double to);
	double RoundTo(double val, int k);
}