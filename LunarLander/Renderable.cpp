#include "Renderable.h"

Renderable::Renderable() {
	SetPosition(Vector2(0, 0)); SetRotation(0); SetDimensions(2, 2);
}


Renderable::Renderable(const Vector2 & position, const float & rotation, float width, float height) {
	SetPosition(position); SetRotation(rotation); SetDimensions(width, height);
}

Renderable::~Renderable() {
}

float Renderable::GetRotation() {
	return rotation;
}

void Renderable::SetRotation(const float & rotation) {
	this->rotation = rotation;
}

Vector2 Renderable::GetPosition() {
	return center;
}

void Renderable::SetPosition(const Vector2 & position) {
	center = position;
}

float Renderable::GetWidth() {
	return dimensions.GetX();
}

void Renderable::SetWidth(const float & width) {
	SetDimensions(width, dimensions.GetY());
}

float Renderable::GetHeight() {
	return dimensions.GetY();
}

void Renderable::SetHeight(const float & height) {
	SetDimensions(dimensions.GetX(), height);
}

void Renderable::SetDimensions(const float & width, const float & height) {
	dimensions.Set(width, height);
	// set the new vertex positions
	float halfWidth = width / 2, halfHeight = height / 2;
	vertices[0] = Vector2(-halfWidth, -halfHeight);
	vertices[1] = Vector2(halfWidth, -halfHeight);
	vertices[2] = Vector2(halfWidth, halfHeight);
	vertices[3] = Vector2(-halfWidth, halfHeight);
}

void Renderable::SetDimensions(const Vector2 & dimensions) {
	Vector2 temp = dimensions;
	SetDimensions(temp.GetX(), temp.GetY());
}

void Renderable::Update(const float & deltaTime) {
	// should be implemented by any updatable derived classes
}

bool Renderable::GetEnabled() {
	return enabled;
}

void Renderable::SetEnabled(const bool & enabled) {
	this->enabled = enabled;
}

std::string Renderable::GetName() {
	return name;
}

Renderable * Renderable::SetName(std::string name) {
	this->name = name;
	return this;
}

