#pragma once
#include "Vector.h"

class Quaternion : public Vector {
public:
    float x, y, z, w;
    /// @param axis Axis to rotate around
    /// @param angle Angle in radians
    Quaternion(const Vector& axis, float angle);
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Quaternion& other);
    Quaternion& operator=(const Quaternion& other);

    float Length() const;
    Quaternion Normalized() const;
    Quaternion Inverted() const;

    Vector Transform(const Vector& vec) const;

    Quaternion operator*(const float& val) const;
    Quaternion operator/(const float& val) const;
    
    Quaternion operator*(const Quaternion& other) const;

    static Quaternion FromVector(const Vector& vector);
};