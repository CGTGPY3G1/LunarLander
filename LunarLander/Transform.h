#pragma once
#include"Vector2.h"

class Transform {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Transform"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="orientation">The orientation.</param>
	Transform(const Vector2 & position, Vector2 & orientation);
	~Transform();
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>the position</returns>
	Vector2 GetPosition();
	/// <summary>
	/// Gets the orientation.
	/// </summary>
	/// <returns>the orientation</returns>
	Vector2 GetOrientation();
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="x">The new x position.</param>
	/// <param name="y">The new y position.</param>
	void SetPosition(const float & x, const float & y);
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="newPosition">The new position.</param>
	void SetPosition(Vector2 & newPosition);
	/// <summary>
	/// Translates the object by the specified amount.
	/// </summary>
	/// <param name="x">The x axis displacement.</param>
	/// <param name="y">The y axis displacement.</param>
	void Translate(const float & x, const float & y);
	/// <summary>
	/// Translates the object by the specified amount.
	/// </summary>
	/// <param name="amount">The displacement amount.</param>
	void Translate(Vector2 & amount);
	/// <summary>
	/// Rotates the object by the specified angle.
	/// </summary>
	/// <param name="angle">The angle.</param>
	void Rotate(const float & angle);
	/// <summary>
	/// Rotates the object by the specified vector.
	/// </summary>
	/// <param name="amount">The rotation vector.</param>
	void Rotate(Vector2 & amount);
private:
	/// <summary>
	/// Resets this instance.
	/// </summary>
	void Reset();
	Vector2 position, orientation;
};

