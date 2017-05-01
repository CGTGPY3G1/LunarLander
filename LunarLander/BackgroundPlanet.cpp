#include "BackgroundPlanet.h"
#include "Transform.h"
#include "MyMath.h"
#include "Random.h"
#include "Image.h"
#include <sstream>

BackgroundPlanet::BackgroundPlanet(const Vector2 & position, Vector2 & orientation, const Vector2 & orbitPosition) : GameObject(position, orientation) {
	this->orbitPosition = orbitPosition; 
	// use a pseudorandom boolean to 
	// determine if the planet should move
	moving = Random::RandomBool();
	// pseudorandomly set the orbit rage
	float orbitX, orbitY;
	if(moving) { // if the planet should move
		orbitX = Random::RandomFloat(600, 1000);
		orbitY = Random::Random::RandomFloat(300, 600);
		// reverses each range if pseudorandom booleans are true
		if(Random::RandomBool()) orbitX *= -1;
		if(Random::RandomBool()) orbitY *= -1;
		// pseudorandomly set the number of orbits per second
		oPS = Random::RandomFloat(0.01f, 0.025f);
	}
	else {
		orbitX = Random::RandomFloat(-400, 400);
		orbitY = Random::Random::RandomFloat(300, 600);
	}
	this->orbitRange.Set(orbitX, orbitY);
	this->orbitRange = orbitRange;
	transform->SetPosition(this->orbitPosition + this->orbitRange);
	// get pseudorandom booleans that will determine the direction of the planets orbit and rotation
	rotateClockWise = Random::RandomBool(); orbitClockWise = Random::RandomBool();
	rPS = Random::RandomFloat(0.1f);
	// get a pseudorandom size for the planet
	float planetSize = Random::RandomFloat(50, 500);
	std::stringstream imageName;
	// select 1 of the 16 available planet images
	imageName << "planet" << Random::RandomInt(1, 17) << ".png";
	AddRenderable((new Image(imageName.str().c_str(), planetSize, planetSize))->SetName("Planet"));
	// set the planet to a pseudorandom rotation
	transform->Rotate(Random::RandomFloat(0, MyMath::TAU()));
	rotation = (transform->GetPosition() - this->orbitPosition).AngleInRadians();
}

BackgroundPlanet::~BackgroundPlanet() {

}

void BackgroundPlanet::Update(const float & deltaTime) {
	if(!stopped) {
		// get the amount to rotate in radians
		const float TWO_PI = MyMath::TAU();
		float toRotate = (rPS * TWO_PI) * deltaTime;
		// if the planet rotates clockwise
		// make the value negative
		if(rotateClockWise) toRotate *= -1;
		// rotate the GameObject
		transform->Rotate(toRotate);
		if(moving) { // if the planet moves
			// same as above but for orbits
			toRotate = (oPS * TWO_PI) * deltaTime;
			if(orbitClockWise) toRotate *= -1;
			rotation += toRotate;
			if(rotation > TWO_PI) rotation -= TWO_PI;
			// set the new orbit position
			Vector2 newPosition = Vector2(orbitRange.GetX() * cosf(rotation), orbitRange.GetY() * sinf(rotation));
			transform->SetPosition(orbitPosition + newPosition);
		}
	}
}
 