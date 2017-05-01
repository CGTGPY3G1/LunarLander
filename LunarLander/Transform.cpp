#include"Transform.h"

Transform::Transform(const Vector2 & position, Vector2 & orientation) {
	this->position = position;
	this->orientation = orientation.Normalized();
}

Vector2 Transform::GetPosition() {
	return position;
}

Vector2 Transform::GetOrientation() {
	return orientation;
}

void Transform::SetPosition(const float & x, const float & y) {
	position.Set(x, y);
}

void Transform::SetPosition(Vector2 & newPosition) {
	position = newPosition;
}

void Transform::Translate(const float & x, const float & y) {
	position.Add(x, y);
}

void Transform::Translate(Vector2 & amount) {
	position += amount;
}

void Transform::Rotate(const float & angleInRadians) {
	orientation.RotateInRadians(angleInRadians);
}

void Transform::Rotate(Vector2 & amount) {
	orientation.RotateInRadians(amount.AngleInRadians());
}

Transform::~Transform() {
}

void Transform::Reset() {
	position = Vector2(0, 0);
	orientation = Vector2(1, 0);
}
