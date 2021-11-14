#include "Utils.h"

double Utils::RandRange(double from, double to) {
	return ((double)rand() / RAND_MAX) * (to - from) + from;
}
double Utils::RandRange(double to) {
	return RandRange(0, to);
}

double Utils::RoundTo(double val, int k) {
	val *= pow(10, k);
	val = round(val);
	val /= pow(10, k);

	if (fabs(val) == 0)
		val = 0;

	return val;
}