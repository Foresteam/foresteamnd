#include "Vector.h"
using namespace std;

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector::Vector(const Vector& other) : Vector(other.x, other.y, other.z) {}
Vector::Vector() : Vector::Vector(0, 0, 0) {}
Vector& Vector::operator=(const Vector& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool Vector::operator<(const Vector& v) const {
	if (std::min(std::min(x, y), z) < std::min(std::min(v.x, v.y), v.z))
		return true;
	else if (std::min(std::min(v.x, v.y), v.z) < std::min(std::min(x, y), z))
		return false;
	else
		return std::max(std::max(x, y), z) < std::max(std::max(v.x, v.y), v.z);
	// return this->x < v.x && this->y < v.y && this->z < v.z;
}
bool Vector::operator>(const Vector& v) const {
	return !(*this < v);
}
Vector Vector::operator+(const Vector& v2) const {
	return Vector(x + v2.x, y + v2.y, z + v2.z);
}
Vector Vector::operator-(const Vector& v2) const {
	return Vector(x - v2.x, y - v2.y, z - v2.z);
}
void Vector::operator-=(const Vector& v2) {
	*this = *this - v2;
}
void Vector::operator+=(const Vector& v2) {
	*this = *this + v2;
}
float Vector::operator*(const Vector& v2) const {
	return this->Dot(v2);
}
Vector Vector::operator/(const float& n) const {
	return Vector(x / n, y / n, z / n);
}
Vector Vector::operator*(const float& n) const {
	return Vector(x * n, y * n, z * n);
}
bool Vector::operator==(const Vector& v2) const {
	return x == v2.x && y == v2.y && z == v2.z;
}

Vector Vector::Cross(const Vector& v2) const {
	Vector out = Vector();
	out.x = y * v2.z - z * v2.y;
	out.y = z * v2.x - x * v2.z;
	out.z = x * v2.y - y * v2.x;
	return out;
}
float Vector::Dot(const Vector& v2) const {
	float prod = 0;
	prod += x * v2.x;
	prod += y * v2.y;
	prod += z * v2.z;
	return prod;
}
float Vector::Distance(const Vector& v2) const {
	return sqrt(pow(x - v2.x, 2) + pow(y - v2.y, 2) + pow(z - v2.z, 2));
}
float Vector::Length() const {
	return Distance(Vector(0, 0, 0));
}
Vector Vector::Normalized() const {
	return *this / Length();
}
Vector Vector::Angle() const {
	Vector out = Vector();
	out.x = atan2(y, x);
	out.y = atan2(x, z);
	return out;
}
string Vector::ToString() const {
	stringstream ss;
	ss << "(";
	ss << x;
	ss << ", ";
	ss << y;
	ss << ", ";
	ss << z;
	ss << ")";

	return string(istreambuf_iterator<char>(ss), {});
}