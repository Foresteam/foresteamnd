#pragma once
#include "Utils.h"
#include <sstream>
#include <fstream>
using namespace std;

template<template<typename> typename T>
T<string> Utils::ReadAllFile(string name) {
	auto result = T<string>();
	ifstream input;
	input.open(name);
	for (string line = ""; getline(input, line);)
		result.push_back(line);
	return result;
}

template <template <typename> typename T>
T<string> Utils::String::Split(string s, string delimiter) {
	T<string> result = T<string>();
	size_t pos;
	while ((pos = s.find(delimiter)) != string::npos) {
		string found = s.substr(0, pos);
		if (found.length() > 0)
			result.push_back(s.substr(0, pos));
		s = s.substr(pos + 1);
	}
	if (s.length() > 0)
		result.push_back(s);
	return result;
}

template <template <typename> typename T, typename V>
string Utils::String::Join(T<V> items, string glue) {
    stringstream ss;
    int i = 0;
    for (V item : items) {
        ss << item;
        if (i != items.size() - 1)
            ss << glue;
        i++;
    }
    return string(istreambuf_iterator<char>(ss), {});
}
template<typename T>
string Utils::String::Convert(T value) {
	string rs;

	stringstream ss;
	ss << value;
	ss >> rs;

	return rs;
}
template<typename T>
T Utils::String::Convert(string value) {
    T rs;
    stringstream ss;
    ss << value;
    ss >> rs;
    return rs;
}