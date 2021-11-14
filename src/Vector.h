#pragma once
#include <cmath>
#include <sstream>
#include <string>

class Vector {
public:
	double x, y, z;
	Vector(double x, double y, double z);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	Vector();

	bool operator<(const Vector& v) const;
	bool operator>(const Vector& v) const;
	Vector operator+(const Vector& v2) const;
	Vector operator-(const Vector& v2) const;
	void operator-=(const Vector& v2);
	void operator+=(const Vector& v2);
	double operator*(const Vector& v2) const;
	Vector operator/(const double& n) const;
	Vector operator*(const double& n) const;
	bool operator==(const Vector& v2) const;

	// For rendering.
	Vector WrapScreen();
	// @param v2 Other Vector
	// @return The cross product of the vector and v2
	Vector Cross(const Vector& v2) const;
	// @param v2 Other Vector
	// @return The dot product of the vector and v2
	double Dot(const Vector& v2) const;
	// @param v2 Other Vector
	// @return The distance between the vector and v2
	double Distance(const Vector& v2) const;
	double Length() const;
	// @return Vector with length of 1
	Vector Normalized() const;
	Vector Angle() const;
	
	// @return (x, y, z)
	std::string virtual ToString() const;
};