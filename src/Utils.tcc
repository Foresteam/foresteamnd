#pragma once
#include "Utils.h"
#include <sstream>
#include <fstream>
#include <list>

template<template<typename> typename T>
T<std::string> Utils::ReadAllFile(std::string name) {
	auto result = T<std::string>();
	std::ifstream input;
	input.open(name);
	for (std::string line = ""; getline(input, line);)
		result.push_back(line);
	return result;
}

template <template <typename> typename T>
T<std::string> Utils::String::Split(std::string s, std::string delimiter) {
	T<std::string> result = T<std::string>();
	size_t pos;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		std::string found = s.substr(0, pos);
		if (found.length() > 0)
			result.push_back(s.substr(0, pos));
		s = s.substr(pos + 1);
	}
	if (s.length() > 0)
		result.push_back(s);
	return result;
}

template <template <typename> typename T, typename V>
std::string Utils::String::Join(T<V> items, std::string glue) {
    std::stringstream ss;
    int i = 0;
    for (V item : items) {
        ss << item;
        if (i != items.size() - 1)
            ss << glue;
        i++;
    }
    return std::string(std::istreambuf_iterator<char>(ss), {});
}
template <typename T>
std::string Utils::String::Convert(T value) {
	std::string rs;

	std::stringstream ss;
	ss << value;
	ss >> rs;

	return rs;
}
template<typename T>
T Utils::String::Convert(std::string value) {
    T rs;
    std::stringstream ss;
    ss << value;
    ss >> rs;
    return rs;
}

int Utils::String::Regex::CountMatches(std::string s, std::regex expr) {
	auto wordsBegin = std::sregex_iterator(s.begin(), s.end(), expr);
	auto wordsEnd = std::sregex_iterator();

	return std::distance(wordsBegin, wordsEnd);
}
template <template <typename> typename T>
T<std::smatch> Utils::String::Regex::FindAllMatches(std::string s, std::regex expr) {
	T<std::smatch> result = T<std::smatch>();
	std::smatch sm;
	while (std::regex_search(s, sm, expr)) {
		result.push_back(sm);
		s = sm.suffix();
	}
	return result;
}
std::set<std::string> Utils::String::Regex::FindAllMatchesOnce(std::string s, std::regex expr) {
	std::set<std::string> result = std::set<std::string>();
	for (auto match : FindAllMatches<std::list>(s, expr))
		result.emplace(match.str());
	return result;
}