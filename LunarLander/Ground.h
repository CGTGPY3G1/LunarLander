#pragma once
#include "GameObject.h"
class Ground : public GameObject {
public:
	/// <summary>
	/// Ground costrctor.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="orientation">The orientation.</param>
	/// <param name="width">The world width.</param>
	/// <param name="height">The world height.</param>
	/// <param name="noOfSections">The no of sections.</param>
	Ground(const Vector2 & position, Vector2 & orientation, const float & width, const float & height, int noOfSections);
	~Ground();
private:
	/// <summary>
	/// Builds the ground.
	/// </summary>
	/// <param name="width">The world width.</param>
	/// <param name="height">The world height.</param>
	/// <param name="noOfSections">The no of sections.</param>
	void BuildGround(const float & width, const float & height, int noOfSections);
private:
	Vector2 landingLocation;// the location of the landing pad
};
