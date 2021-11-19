#include "DynamicR2.h"
#include <cstring>

#define TDR2 template<typename T>

TDR2 DynamicR2<T>::DynamicR2(size_t s1, size_t s2) {
    this->s1 = s1;
    this->s2 = s2;
    _self = new T[s1 * s2];
    self = new T*[s2];
    for (size_t i = 0; i < s2; i++)
        self[i] = _self + s1 * i;
}
TDR2 DynamicR2<T>::DynamicR2(const DynamicR2& other) : DynamicR2(other.s1, other.s2) {
    memcpy(_self, other._self, s1 * s2);
}

TDR2 DynamicR2<T> DynamicR2<T>::operator=(const DynamicR2& other) {
    return DynamicR2<T>(other);
}

TDR2 DynamicR2<T>::~DynamicR2() {
    delete[] _self;
    delete[] self;
}

TDR2 T* DynamicR2<T>::At(size_t index) {
    return self[index];
}
TDR2 T* DynamicR2<T>::operator[](size_t index) {
    return At(index);
}