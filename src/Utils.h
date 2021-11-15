#pragma once
#include <random>
#include <string>

#define sqr(x) x * x

#define DEG2RAD M_PI / 180
#define dsin(arg)  sin(arg * DEG2RAD)
#define dcos(arg)  cos(arg * DEG2RAD)
#define dtan(arg)  tan(arg * DEG2RAD)
#define dasin(arg) asin(arg) / DEG2RAD
#define dacos(arg) acos(arg) / DEG2RAD
#define datan(arg) atan(arg) / DEG2RAD

namespace Utils {
    /// @param from Random start
    /// @param to Random end
    /// @return Random value in range [from, to]
    float RandRange(float from, float to);
	/// @param to Random end
	/// @return Random value in range [0, to]
	float RandRange(float to);
	float RoundTo(float val, int k);
    /// @returns A string like (a, b, c)
    std::string WrappedInBrackets(int count...);
}