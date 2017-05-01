#include "Shape.h"
#include <Windows.h>

Shape::Shape(const Vector2 & center) : Renderable() {
	this->center = center;
}

Shape::~Shape() {
}

void Shape::Draw(const Vector2 &origin, const float & rotation) {
	if(enabled) {
		glDisable(GL_TEXTURE_2D); //disable textures
		glColor4f(r, g, b, 1.0f);
		glBegin(drawStyle);
		Vector2 position;
		int noOfVerts = GetVertexCount();
		for(int index = 0; index < noOfVerts; index++) {
			//add the shapes rotation to the containing objects rotation
			float toRotate = this->rotation + rotation;
			// calculate the transformed position of the vetices relevant to the specified origin and rotation
			position = origin + (toRotate != 0 ? (center + vertices[index]).RotateInRadians(toRotate) : (center + vertices[index]));
			glVertex2d(position.GetX(), position.GetY());
		}
		glEnd();
	}
}

Shape * Shape::SetColour(const float & r, const float & g, const float & b, const float & a) {
	this->r = r; this->g = g; this->b = b; this->a = a;
	return this;
}

int Shape::GetDrawStyle() {
	return drawStyle;
}

Shape * Shape::SetDrawStyle(const int & newDrawStyle) {
	if(drawStyle <= GL_POLYGON)
		drawStyle = newDrawStyle;
	return this;
}

float Shape::GetRadius() {
	return radius;
}

void Shape::CalculateRadius() {
	// calulate the raius as the length of the furthest vertex
	unsigned int noOfVerts = vertices.size();
	float length = 0.0;
	for(unsigned int i = 0; i < noOfVerts; i++) {
		float sqrMagnitude = vertices[i].SquareMagnitude();
		if(sqrMagnitude > length)
			length = sqrMagnitude;
	}
	SetRadius(sqrt(length));
}

float Shape::GetSquaredRadius() {
	return sqrRadius;
}

int Shape::GetVertexCount() {
	return vertices.size();
}

std::vector<Vector2> Shape::GetTransformed(const Vector2 & origin, const float & rotation) {
	std::vector<Vector2> toReturn;
	size_t noOfVerts = vertices.size();
	for(size_t i = 0; i < noOfVerts; i++) {
		//add the shapes rotation to the containing objects rotation
		float toRotate = this->rotation + rotation;
		// calculate the transformed position of the vetices relevant to the specified origin and rotation
		toReturn.push_back(origin + (center + vertices[i]).RotateInRadians(toRotate));
	}
	return toReturn;
}

RenderableType Shape::GetType() {
	return SHAPE;
}

void Shape::SetRadius(float radius) {
	this->radius = radius; sqrRadius = radius * radius;
}