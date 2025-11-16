#pragma once
#include <cmath>

class Vector
{
public:
	double x, y;


	Vector() = default;
	Vector(double x, double y);
	void Set(double x_val, double y_val);

	float Dot(const Vector other) const;
	double Magnitude() const;
	Vector Normalize() const;

	Vector operator+(const Vector other) const;
	Vector operator-(const Vector other) const;
	Vector operator*(const float scalar) const;
	Vector operator/(const float scalar) const;
};