#pragma once


class Vector2{


public:
	Vector2();
	Vector2(const float & x, const float & y);
	~Vector2();
	float GetX();
	void SetX(const float & x);
	float GetY();
	void SetY(const float & y);
	Vector2 Set(const float & x, const float & y);
	Vector2 operator = (Vector2 toSet);
	Vector2 Add(const float & x, const float & y);
	Vector2 operator + (Vector2 toAdd);
	const Vector2 operator + (const Vector2 & toAdd) const;
	Vector2 operator += (Vector2 toAdd);
	Vector2 Subtract(const float & x, const float & y);
	Vector2 operator - (Vector2 toSubtract);
	const Vector2 operator - (const Vector2 & toSubtract) const;
	Vector2 operator -= (Vector2 toSubtract);
	Vector2 Scale(const float & scalar);
	Vector2 operator * (const float & scalar);
	Vector2 operator / (const float & scalar);
	float Dot(Vector2 other);
	float Dot(const float & x, const float & y);
	Vector2 Normalize();
	Vector2 Normalized();
	float SquareMagnitude();
	float Magnitude();
	float AngleInRadians();
	Vector2 RotateInRadians(const float & angle);
	Vector2 RotatedInRadians(const float & angle);
	/// <summary>
	/// rotates the object 90 degrees in the specified direction.
	/// </summary>
	/// <param name="clockwise">the direction (true if clockwise).</param>
	/// <returns>this</returns>
	Vector2 Flip90(const bool & clockwise);
private:
	float x, y;
};
