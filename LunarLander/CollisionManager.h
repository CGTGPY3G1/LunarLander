#pragma once
#include <vector>
#include "Vector2.h"
#include "Shape.h"

class GameObject;

class CollisionManager {
public:
	/// <summary>
	/// Checks for collisions between 2 objects.
	/// </summary>
	/// <param name="object1">The first object.</param>
	/// <param name="object2">The second object.</param>
	/// <returns>true if colliding, else false</returns>
	static bool CheckCollision(GameObject * object1, GameObject * object2);
private:
	/// <summary>
	/// Checks for collisions between 2 circles.
	/// </summary>
	/// <param name="position1">The first objects position.</param>
	/// <param name="radius1">The first objects radius.</param>
	/// <param name="position2">The second object position.</param>
	/// <param name="radius2">The second object radius.</param>
	/// <returns></returns>
	static bool CheckCircles(const Vector2 & position1, const float & radius1, const Vector2 & position2, const float & radius2);
	/// <summary>
	/// Checks for collisions between 2 polygons.
	/// </summary>
	/// <param name="poly1">The first polygon.</param>
	/// <param name="poly2">The second polygon.</param>
	/// <returns>true if colliding, else false</returns>
	static bool CheckConvexPoly(std::vector<Vector2> & poly1, std::vector<Vector2> & poly2);
	/// <summary>
	/// Projects a polygon on to an axis.
	/// </summary>
	/// <param name="poly">The polygon.</param>
	/// <param name="axis">The axis.</param>
	/// <returns>a Vector2 representing the minimun and maximum points of the projected axis</returns>
	static Vector2 ProjectOnAxis(std::vector<Vector2>& poly, Vector2 & axis);
	/// <summary>
	/// Checks for gaps between 2 min/max pairs.
	/// </summary>
	/// <param name="p1">The first min/max pair.</param>
	/// <param name="p2">The second min/max pair.</param>
	/// <returns></returns>
	static bool MinMaxGap(Vector2 & p1, Vector2 & p2);
};