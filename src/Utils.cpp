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

string Utils::String::AlignedLeft(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength)
		s.insert(s.begin(), ' ');
	return s;
}
string Utils::String::AlignedRight(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength)
		s.insert(s.rbegin().base(), ' ');
	return s;
}
string Utils::String::AlignedCenter(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength) {
		s.insert(s.begin(), ' ');
		s.insert(s.rbegin().base(), ' ');
	}
	if (s.length() > maxLength)
		s.erase(s.rend().base());
	return s;
}

string Utils::String::TrimmedLeft(string s) {
	int spos = 0;
	for (int i = 0; i < s.length() && s[i] == ' '; i++, spos++);
	return s.substr(spos);
}
string Utils::String::TrimmedRight(string s) {
	int spos = 0;
	for (int i = s.length() - 1; i >= 0 && s[i] == ' '; i--, spos++);
	return s.substr(0, s.length() - spos);
}
string Utils::String::Trimmed(string s) {
	return TrimmedRight(TrimmedLeft(s));
}

string Utils::String::ReplacedAll(string s, string what, string with) {
	size_t pos;
	do {
		pos = s.find(what);
		if (pos >= 0)
			s = s.replace(pos, what.length(), with);
	}
	while (pos >= 0);
	return s;
}