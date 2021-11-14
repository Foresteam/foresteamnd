#pragma once
#include "Vector2.h"
#include "Quaternion.h"

class Triangle {
private:
	float sign(Vector2 p1, Vector2 p2, Vector2 p3);
	Vector verteces[3];
    Vector* base;
    Quaternion rotation;
public:
    Vector _points[3];
	Triangle(Vector a, Vector b, Vector c);
    void CalcVerteces(Vector* base);

    Vector GetPoint(int n);
    Vector* GetPoints();
    void Rotate(Quaternion rotation);

	bool Contains(Vector2 point);
    Vector GetNormal();
    Vector GetPointProjection(Vector point);
};