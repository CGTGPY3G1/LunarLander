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
	Poly(const Vector2 & center, const std::vector<Vector2> vertices);
	~Poly();
	/// <summary>
	/// Copies this instance.
	/// </summary>
	/// <returns>a copy of this shape</returns>
	Shape * Copy() override;
};

