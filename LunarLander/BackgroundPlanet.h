#pragma once
#include "GameObject.h"
class BackgroundPlanet : public GameObject {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="BackgroundPlanet"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="orientation">The orientation.</param>
	/// <param name="orbitPosition">The orbit position.</param>
	BackgroundPlanet(const Vector2 & position, Vector2 & orientation, const Vector2 & orbitPosition);
	~BackgroundPlanet();
	/// <summary>
	/// Updates the object by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	void Update(const float & deltaTime) override;
private:
	Vector2 orbitPosition, orbitRange;
	float rPS = 0, oPS = 0; // rotations and orbits per second
	float rotation = 0;
	bool rotateClockWise, orbitClockWise, moving;
};
