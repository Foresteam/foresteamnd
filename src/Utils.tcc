#include "Utils.h"
#include <sstream>
using namespace std;

template <typename T>
string Utils::String::Join(vector<T> items, string glue) {
    stringstream ss;
    for (auto it = items.begin(); it != items.end(); it++) {
        ss << *it;
        if (it != items.rbegin().base())
            ss << glue;
    }

    return string(istreambuf_iterator<char>(ss), {});
}