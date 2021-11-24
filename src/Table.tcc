#pragma once
#include "Table.h"
#include "Utils.tcc"
#include <cstring>

#define TDR2 template<typename T>

TDR2 Table<T>::Table(size_t s1, size_t s2) {
    this->s1 = s1;
    this->s2 = s2;
    _self = new T[s1 * s2];
    self = new T*[s2];
    for (size_t i = 0; i < s2; i++)
        self[i] = _self + s1 * i;
}
TDR2 Table<T>::Table(const Table& other) : Table(other.s1, other.s2) {
    memcpy(_self, other._self, s1 * s2);
}

TDR2 Table<T> Table<T>::operator=(const Table& other) {
    return Table<T>(other);
}

TDR2 Table<T>::~Table() {
    delete[] _self;
    delete[] self;
}

TDR2 T* Table<T>::At(size_t index) {
    return self[index];
}
TDR2 T* Table<T>::operator[](size_t index) {
    return At(index);
}

TDR2 size_t Table<T>::SizeHigh() {
    return s2;
}
TDR2 size_t Table<T>::SizeLow() {
    return s1;
}
TDR2 size_t Table<T>::Size() {
    return SizeHigh();
}

TDR2 std::string Table<T>::ToString() {
    std::string result;
    for (int i = 0; i < SizeHigh(); i++) {
        for (int j = 0; j < SizeLow(); j++) {
            result += Utils::String::Convert(At(i)[j]);
            if (j != SizeLow() - 1)
                result += '\t';
        }
        if (i != SizeHigh() - 1)
            result += '\n';
    }
    return result;
}