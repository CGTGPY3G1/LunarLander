#include "Polygon.h"

Poly::Poly(const Vector2 & center, const std::vector<Vector2> vertices) : Shape(center) {
	this->center = center;
	for(unsigned int i = 0; i < vertices.size(); i++) {
		this->vertices.push_back(vertices[i]);
	}
	CalculateRadius();
}

Poly::~Poly() {
}

Shape * Poly::Copy() {
	Shape * toReturn = new Poly(center, vertices);
	toReturn->SetColour(r, g, b, a);
	toReturn->SetDrawStyle(drawStyle);
	toReturn->SetDimensions(dimensions);
	toReturn->SetRadius(radius);
	SetPosition(GetPosition());
	toReturn->SetName(name);
	return toReturn;
}

