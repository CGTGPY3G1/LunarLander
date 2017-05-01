#pragma once
#include<gl/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "Renderable.h"

class Shape : public Renderable {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Shape"/> class.
	/// </summary>
	/// <param name="center">The center.</param>
	Shape(const Vector2 & center);
	virtual ~Shape();
	/// <summary>
	/// Draws the shape to the screen.
	/// </summary>
	/// <param name="origin">The origin.</param>
	/// <param name="rotation">The rotation.</param>
	void Draw(const Vector2 & origin, const float & rotation) override;
	/// <summary>
	/// Sets the colour.
	/// </summary>
	/// <param name="r">The amount of red in the colour.</param>
	/// <param name="g">The amount of green in the colour.</param>
	/// <param name="b">The amount of blue in the colour.</param>
	/// <param name="a">The amount of alpha (opacity) in the colour.</param>
	/// <returns>this</returns>
	Shape * SetColour(const float & r, const float & g, const float & b, const float & a);
	/// <summary>
	/// Gets the draw style.
	/// </summary>
	/// <returns>an integer representing the draw style</returns>
	int GetDrawStyle();
	/// <summary>
	/// Sets the draw style.
	/// </summary>
	/// <param name="newDrawStyle">The new draw style.</param>
	/// <returns>this</returns>
	Shape * SetDrawStyle(const int & newDrawStyle);
	/// <summary>
	/// Gets the shapes radius.
	/// </summary>
	/// <returns>the radius</returns>
	float GetRadius();
	/// <summary>
	/// Gets the shapes squared radius.
	/// </summary>
	/// <returns>the squared radius</returns>
	float GetSquaredRadius();
	/// <summary>
	/// Gets the vertex count.
	/// </summary>
	/// <returns>the number of vertices in the shape</returns>
	int GetVertexCount();
	/// <summary>
	/// Gets the vertices of this shape with the position  
	/// and rotation of the object applied to them.
	/// </summary>
	/// <param name="origin">The origin.</param>
	/// <param name="rotation">The rotation.</param>
	/// <returns>the transformed vertices of the shape</returns>
	std::vector <Vector2> GetTransformed(const Vector2 & origin, const float & rotation);
	/// <summary>
	/// Gets the Renderable Type.
	/// </summary>
	/// <returns>the RenderableType</returns>
	RenderableType GetType() override;
	/// <summary>
	/// Copies this instance.
	/// </summary>
	/// <returns>a copy of this</returns>
	virtual Shape * Copy() = 0;
	/// <summary>
	/// Sets the radius.
	/// </summary>
	/// <param name="radius">The radius.</param>
	void SetRadius(float radius);
protected:
	/// <summary>
	/// Calculates and sets the radius.
	/// </summary>
	void CalculateRadius();
	std::vector <Vector2> vertices;
	float radius = 0, sqrRadius = 0, r = 0, g = 0, b = 0, a = 1;
	int drawStyle = GL_POLYGON;
};
