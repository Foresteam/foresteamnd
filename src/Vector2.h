#pragma once
#include "Vector.h"

class Vector2 : public Vector {
public:
	Vector2(float x, float y);
	Vector2(const Vector& other);
	Vector2();
	/// @returns (x, y)
	std::string ToString() const override;
};