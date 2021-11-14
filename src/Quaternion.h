#pragma once
#include "Vector.h"

class Quaternion : public Vector {
public:
    double x, y, z, w;
    /// @param axis Axis to rotate around
    /// @param angle Angle in radians
    Quaternion(const Vector& axis, double angle);
    Quaternion(double x, double y, double z, double w);
    Quaternion(const Quaternion& other);
    Quaternion& operator=(const Quaternion& other);

    double Length() const;
    Quaternion Normalized() const;
    Quaternion Inverted() const;

    Vector Transform(const Vector& vec) const;

    Quaternion operator*(const double& val) const;
    Quaternion operator/(const double& val) const;
    
    Quaternion operator*(const Quaternion& other) const;

    static Quaternion FromVector(const Vector& vector);
};