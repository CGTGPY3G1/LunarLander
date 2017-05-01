#pragma once
#include "GameObject.h"
class Lander : public GameObject {
public:
	Lander(const Vector2 & position, Vector2 & orientation);
	~Lander();
	/// <summary>
	/// Updates the object by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	void Update(const float & deltaTime) override;
	/// <summary>
	/// Moves the object in the specified direction.
	/// </summary>
	/// <param name="amount">The movement direction.</param>
	void Move(Vector2 & amount) override;
	/// <summary>
	/// Kills the object over the specified time to live.
	/// </summary>
	/// <param name="timeToLive">The time to live.</param>
	void Kill(float timeToLive) override;
	/// <summary>
	/// Gets the Landers fuel.
	/// </summary>
	/// <returns>the amount of fuel</returns>
	float GetFuel();
private:
	// force being applied to the object
	Vector2 force;
	// vertical and horizontal movement scalers
	const float vScaler = 50, hScaler = 25;
	float fuel;
};


