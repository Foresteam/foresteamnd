#pragma once
#include "Vector.h"

class Vector2 : public Vector {
public:
	Vector2(double x, double y);
	Vector2(const Vector& vec);
	Vector2();
	// @return (x, y)
	std::string ToString() const override;
};