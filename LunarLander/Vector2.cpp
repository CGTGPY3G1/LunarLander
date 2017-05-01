#include "Vector2.h"
#include "MyMath.h"
#include<cmath>

Vector2::Vector2() {
	this->x = 0; this->y = 0;
}

Vector2::Vector2(const float & x, const float & y) {
	this->x = x; this->y = y;
}

Vector2::~Vector2() {
}

float Vector2::GetX() {
	return x;
}

void Vector2::SetX(const float & x) {
	this->x = x;
}

float Vector2::GetY() {
	return y;
}

void Vector2::SetY(const float & y) {
	this->y = y;
}

Vector2 Vector2::Set(const float & x, const float & y) {
	this->x = x; this->y = y;
	return *this;
}

Vector2 Vector2::operator = (Vector2 toSet) {
	x = toSet.x; y = toSet.y;
	return *this;
}

Vector2 Vector2::Add(const float & x, const float & y) {
	this->x += x; this->y += y;
	return *this;
}

Vector2 Vector2::operator + (Vector2 toAdd) {
	return Vector2(x + toAdd.x, y + toAdd.y);
}

const Vector2 Vector2::operator + (const Vector2 & toAdd) const {
	return Vector2(x + toAdd.x, y + toAdd.y);;
}

Vector2 Vector2::operator += (Vector2 toAdd) {
	x += toAdd.x; y += toAdd.y;
	return *this;
}

Vector2 Vector2::Subtract(const float & x, const float & y) {
	this->x -= x; this->y -= y;
	return *this;
}

Vector2 Vector2::operator - (Vector2 toSubtract) {
	return Vector2(x - toSubtract.x, y - toSubtract.y);
}

const Vector2 Vector2::operator - (const Vector2 & toSubtract) const {
	return Vector2(x - toSubtract.x, y - toSubtract.y);
}

Vector2 Vector2::operator -= (Vector2 toSubtract) {
	x -= toSubtract.x; y -= toSubtract.y;
	return *this;
}

Vector2 Vector2::Scale(const float & scalar) {
	this->x *= x; this->y *= y;
	return *this;
}

Vector2 Vector2::operator * (const float & scalar) {
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator / (const float & scalar) {
	return Vector2(x / scalar, y / scalar);
}

float Vector2::Dot(Vector2 other) {
	return Dot(other.x, other.y);
}

float Vector2::Dot(const float & x, const float & y) {
	return this->x * x + this->y * y;
}

float Vector2::SquareMagnitude() {
	return x * x + y * y;
}

float Vector2::Magnitude() {
	return sqrt(SquareMagnitude());
}

Vector2 Vector2::Normalize() {
	float magnitude = Magnitude();
	if (magnitude != 0 && magnitude != 1) {
		x /= magnitude;
		y /= magnitude;
	}
	return *this;
}

Vector2 Vector2::Normalized() {
	return Vector2(x, y).Normalize();
}

float Vector2::AngleInRadians() {
	return atan2f(y, x);
}

Vector2 Vector2::RotateInRadians(const float & angle) {
	float cosine = cosf(angle), sine = sinf(angle);
	float rotatedX = (x * cosine) - (y * sine);
	float rotatedY = (x * sine) + (y * cosine);
	x = rotatedX; y = rotatedY;
	return *this;
}

Vector2 Vector2::RotatedInRadians(const float & angle) {
	return Vector2(x, y).RotateInRadians(angle);
}

Vector2 Vector2::Flip90(const bool & clockwise) {
	float oldX = x;
	if (clockwise) {
		x = y;
		y = -oldX;
	}
	else {
		x = -y;
		y = oldX;
	}
	return *this;
}
