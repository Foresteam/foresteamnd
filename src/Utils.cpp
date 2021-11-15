#include "Utils.h"
#include <sstream>
#include <cstdarg>
#include <cmath>
using namespace std;

float Utils::RandRange(float from, float to) {
	return ((float)rand() / RAND_MAX) * (to - from) + from;
}
float Utils::RandRange(float to) {
	return RandRange(0, to);
}

float Utils::RoundTo(float val, int k) {
	val *= pow(10, k);
	val = round(val);
	val /= pow(10, k);

	if (fabs(val) == 0)
		val = 0;

	return val;
}

string Utils::WrappedInBrackets(int count...) {
	va_list args;
	va_start(args, count);

	stringstream ss;
	ss << "(";
	for (int i = 0; i < count; i++) {
		ss << (float)va_arg(args, double);
		if (i != count - 1)
			ss << ", ";
	}
	ss << ")";

	va_end(args);
	return string(istreambuf_iterator<char>(ss), {});
}