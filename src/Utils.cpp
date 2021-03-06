#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdarg>
#include <fstream>
#include <sstream>
using namespace std;

float Utils::RandRange(float from, float to) {
	return ((float)rand() / RAND_MAX) * (to - from) + from;
}
float Utils::RandRange(float to) {
	return RandRange(0, to);
}

float Utils::RoundTo(float val, int k) {
	val *= (float)pow(10, k);
	val = round(val);
	val /= (float)pow(10, k);

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
		s.insert(s.rbegin().base(), ' ');
	return s;
}
string Utils::String::AlignedRight(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength)
		s.insert(s.begin(), ' ');
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
	size_t spos = 0;
	for (size_t i = s.length(); i > 0 && s[i - 1] == ' '; i--, spos++);
	return s.substr(0, s.length() - spos);
}
string Utils::String::Trimmed(string s) {
	return TrimmedRight(TrimmedLeft(s));
}

string Utils::String::ReplaceAll(string s, string what, string with) {
	size_t pos;
	do {
		pos = s.find(what);
		if (pos >= 0)
			s = s.replace(pos, what.length(), with);
	}
	while (pos >= 0);
	return s;
}
string Utils::String::ToLower(string s) {
	transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
	return s;
}

string Utils::Net::ParseHostStr(uint32_t host, uint16_t port) {
	char* hostBytes = reinterpret_cast<char*>(&host);
	return std::to_string(int(hostBytes[0])) + '.' +
		   std::to_string(int(hostBytes[1])) + '.' +
		   std::to_string(int(hostBytes[2])) + '.' +
		   std::to_string(int(hostBytes[3])) + ':' +
		   std::to_string(port);
}