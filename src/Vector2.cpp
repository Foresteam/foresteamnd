#include "Vector2.h"
using namespace std;

Vector2::Vector2(double x, double y) : Vector::Vector(x, y, 0) {}
Vector2::Vector2(const Vector& vec) : Vector2::Vector2(vec.x, vec.y) {}
Vector2::Vector2() : Vector2::Vector2(0, 0) {}
string Vector2::ToString() const {
	stringstream ss;

	ss << "(";
	ss << x;
	ss << ", ";
	ss << y;
	ss << ")";

	return string(istreambuf_iterator<char>(ss), {});
}