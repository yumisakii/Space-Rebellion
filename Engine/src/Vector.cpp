#include "vector.h"

Vector::Vector(double x_val, double y_val) {

	x = x_val;
	y = y_val;

}

void Vector::Set(double x_val, double y_val) {

	x = x_val;
	y = y_val;

}

float Vector::Dot(const Vector other) const {
	return x * other.x + y * other.y;
}

double Vector::Magnitude() const {
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vector Vector::Normalize() const {
	return *this / Magnitude();
}

Vector Vector::operator+(const Vector other) const {
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector other) const {
	return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(const float scalar) const {
	return Vector(x * scalar, y * scalar);
}

Vector Vector::operator/(const float scalar) const {
	return Vector(x / scalar, y / scalar);
}