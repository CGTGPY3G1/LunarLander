#include "Ground.h"
#include "Polygon.h"
#include "Random.h"
#include "Transform.h"


Ground::Ground(const Vector2 & position, Vector2 & orientation, const float & width, const float & height, int noOfSections) : GameObject(position, orientation) {
	BuildGround(width, height, noOfSections);
}

Ground::~Ground() {
}

void Ground::BuildGround(const float & width, const float & height, int noOfSections) {
	// calculate the section width and half width
	float sectionWidth = (width / noOfSections);
	float halfWidth = sectionWidth / 2;
	// pick a section to place the landing pad on
	int landingSection = 1+Random::RandomInt(noOfSections - 2);
	float lastHeight = height; // set a default for last height
	for(int i = 0; i < noOfSections; i++) { // for each section
		float x = (sectionWidth*i); // set the sections start x 
		float y = 0;
		if(i == landingSection) { // if the section is the chosen landing section
			y = lastHeight; // use the last height to make the section flat
			landingLocation = Vector2(x + halfWidth, y); // set the landing location
		}
		else {
			if(i < noOfSections - 1) {// if not the last section
				float min, max;
				min = height * 0.05f; // set the minimum y to 5% of the world height
				// if the current section is 1 before the landing section, set max
				// to 15% of world height else set to 60% of world height
				max = (i == landingSection - 1) ? height * 0.15f : height * 0.6f;
				// set y to pseudorandom value between min and max
				y = Random::RandomFloat(min, max);
				// while the difference between the new height 
				// and the the old height is less than 20
				// get a new random height
				float difference = abs(lastHeight - y);
				while(difference < 20) {
					y = Random::RandomFloat(min, max);
					difference = abs(lastHeight - y);
				}
			}
			else { // if on the last section
				// set the height to the world height
				y = height; 
			}
		}
		
		// create a new shape to use as both renderer and collider
		std::vector<Vector2> shapeData = { Vector2(-halfWidth, 0), Vector2(halfWidth, 0), Vector2(halfWidth, y), Vector2(-halfWidth, lastHeight) };
		Shape * shape = new Poly(Vector2(x+halfWidth, 0) - transform->GetPosition(), shapeData);
		shape->SetName("Ground");
		shape->SetColour(0.4f, 0.4f, 0.4f, 1.0f); // make ground colour dark grey
		AddRenderable(shape->Copy()); // add a copy of the new shape as a renderable
		AddCollider(shape); // then add the original as a collider
		lastHeight = y; // set the last height to the new height
	}
	// create a boundary 4 times higher than the screen height.  making it impossible to traval high enough to get over it with the available fuel
	float boundaryHalfWidth = width / 4, boundaryHalfHeight = height * 2;
	// create the right boundary
	std::vector<Vector2> shapeData = { Vector2(-boundaryHalfWidth, -boundaryHalfHeight),
		Vector2(boundaryHalfWidth, -boundaryHalfHeight), Vector2(boundaryHalfWidth, boundaryHalfHeight), Vector2(-boundaryHalfWidth, boundaryHalfHeight) };
	Shape * boundary = new Poly(Vector2((width/2) + boundaryHalfWidth, boundaryHalfHeight), shapeData);
	boundary->SetName("Ground");
	AddCollider(boundary->Copy()); // add a copy of it as a collider
	// move th original to the other side of the screen
	boundary->SetPosition(Vector2(-boundary->GetPosition().GetX(), boundary->GetPosition().GetY()));
	AddCollider(boundary); // then add it as a collider

	// create a new child GameObject for the landing pad
	GameObject * landingPad = new GameObject(landingLocation, Vector2(1.0f, 0.0f), "LandingPad");
	// use the halfwidth of the segments to set the halfwidth of the landing pad
	float landingHalfWidth = halfWidth * 1.2f; 
	// set the height of the landing pad to a quarter of its width
	float landingHeight = landingHalfWidth * 0.5f;
	// create a new shape to use as both renderer and collider
	shapeData = { Vector2(-landingHalfWidth, 0), Vector2(landingHalfWidth, 0), Vector2(landingHalfWidth, landingHeight), Vector2(-landingHalfWidth, landingHeight) };
	Shape * shape = new Poly(Vector2(0.0f, 0.0f), shapeData);
	// set the shapes dimensions
	shape->SetDimensions(landingHalfWidth * 2, landingHeight);
	shape->SetName("LandingPad");
	// colour it white
	shape->SetColour(1.0f, 1.0f, 1.0f, 0.0f);
	landingPad->AddRenderable(shape->Copy()); // add a copy of the new shape as a renderable
	landingPad->AddCollider(shape); // then add the original as a collider
	AddChild(landingPad); // add the landing pad as a child of the ground
}