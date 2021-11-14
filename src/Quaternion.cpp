#include "Quaternion.h"
#include <cmath>
#include <iostream>
#define sqr(x) x * x

Quaternion::Quaternion(const Vector& axis, double angle) : Vector(axis.Normalized() * sin(angle / 2)) {
    x = Vector::x;
    y = Vector::y;
    z = Vector::z;
    w = cos(angle / 2);
}
Quaternion Quaternion::FromVector(const Vector& vector) {
	return Quaternion(vector.x, vector.y, vector.z, 0);
}
Quaternion::Quaternion(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

double Quaternion::Length() const {
	return sqrt(sqr(x) + sqr(y) + sqr(z) + sqr(w));
}
Quaternion Quaternion::Normalized() const {
    return *this / Length();
}
Quaternion Quaternion::Inverted() const {
    return Quaternion(-x, -y, -z, w).Normalized();
}

Vector Quaternion::Transform(const Vector& vec) const {
	Quaternion r = *this * FromVector(vec) * this->Inverted();
    return Vector(r.x, r.y, r.z);
}

Quaternion Quaternion::operator*(const double& val) const {
    return Quaternion(x * val, y * val, z * val, w * val);
}
Quaternion Quaternion::operator/(const double& val) const {
	return *this * (1 / val);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion& Quaternion::operator=(const Quaternion& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}
Quaternion::Quaternion(const Quaternion& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}