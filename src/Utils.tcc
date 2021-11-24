#pragma once
#include "Utils.h"
#include <sstream>
using namespace std;

template <typename T>
string Utils::String::Join(list<T> items, string glue) {
    stringstream ss;
    int i = 0;
    for (T item : items) {
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