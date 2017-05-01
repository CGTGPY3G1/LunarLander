#include "Polygon.h"


Poly::Poly(const Vector2 & center, const std::vector<Vector2> & vertices) : Shape(center) {
	this->vertices = vertices;
	CalculateRadius();
}

Poly::Poly(const Vector2 & center, const unsigned int & noOfVerts, const Vector2 vertices...) : Shape(center) {
	// create a variable arguments list and use it to gain access to the vertices.. Variadic arguments
	va_list vectors;
	va_start(vectors, vertices);
	// add each of the arguments to the vertices array
	this->vertices.push_back(vertices);
	for(unsigned int i = 0; i < noOfVerts - 1; i++) {
		this->vertices.push_back(va_arg(vectors, Vector2));
	}
	// stop using the variable arguments list 
	va_end(vectors);
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

