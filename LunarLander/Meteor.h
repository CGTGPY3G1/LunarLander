#pragma once
#include "GameObject.h"

class Meteor : public GameObject{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Meteor"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="orientation">The orientation.</param>
	/// <param name="velocity">The velocity.</param>
	Meteor(const Vector2 & position, Vector2 & orientation, Vector2 & velocity);
	~Meteor();
	/// <summary>
	/// Updates the object by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	void Update(const float & deltaTime) override;
	/// <summary>
	/// Kills the object over the specified time to live.
	/// </summary>
	/// <param name="timeToLive">The time to live.</param>
	void Kill(float timeToLive) override;
private:
	Vector2 velocity;
	float rotationSpeed = 0;
};

