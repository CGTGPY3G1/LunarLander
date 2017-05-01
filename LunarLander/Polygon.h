#pragma once
#include "Shape.h"
#include <cstdarg>

class Poly : public Shape {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Poly" /> class.
	/// </summary>
	/// <param name="center">The center.</param>
	/// <param name="vertices">The vertices.</param>
	Poly(const Vector2 & center, const std::vector<Vector2> & vertices);
	/// <summary>
	/// Initializes a new instance of the <see cref="Poly"/> class. (Uses Variadic arguments)
	/// </summary>
	/// <param name="center">The center.</param>
	/// <param name="noOfVerts">The number of vertices.</param>
	/// <param name="vertices...">any number of vector2 arguments (only first (noOfVerts) will be used)</param>
	Poly(const Vector2 & center, const unsigned int & noOfVerts, const Vector2 vertices...);
	~Poly();
	/// <summary>
	/// Copies this instance.
	/// </summary>
	/// <returns>a copy of this shape</returns>
	Shape * Copy() override;
};

