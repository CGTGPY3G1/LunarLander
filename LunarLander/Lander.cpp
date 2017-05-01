#include "Lander.h"
#include "Transform.h"
#include <string>
#include<sstream>
#include "Animation.h"
#include "Polygon.h"

// constant vecotor2's used for gravitational force as well as up and down directions 
const Vector2 GRAVITY = Vector2(0.0f, -20.0f), UP = Vector2(0.0f, 1.0f), RIGHT = Vector2(1.0f, 0.0f);
const float MAX_FUEL = 100.0F, FUEL_REDUCTION_RATE = 10.0f; // the maximum fuel and the rate it reduces at
/// <summary>
/// Initializes a new instance of the <see cref="Lander"/> class.
/// </summary>
/// <param name="position">The position.</param>
/// <param name="orientation">The orientation.</param>
Lander::Lander(const Vector2 & position, Vector2 & orientation) : GameObject(position, orientation) {
	float animWidth = 10, animHeight = 15;
	fuel = MAX_FUEL;
	// create a new animation with the specified width and height
	Animation *thrustAnim = new Animation(Vector2(0, -20), animWidth, animHeight);
	thrustAnim->SetName("Thrust"); // name the animation
	thrustAnim->SetEnabled(false); // set it as disabled
	thrustAnim->SetSwitchRate(1.0f / 11.0f); // set the frame switch rate in seconds
	for(int i = 1; i < 12; i++) { // load each frame and add them to the animation
		std::stringstream s;
		s << "thrust" << i << ".png";
		thrustAnim->AddFrame(new Image(s.str().c_str(), animWidth, animHeight));
	}
	AddRenderable(thrustAnim); // add the animation to the GameObject	
	// add the lander image to the GameObject
	AddRenderable((new Image("lander.png", 20, 35))->SetName("Lander"));
	float explosionSize = 100.0f;
	// same as above
	Animation *explosionAnim = new Animation(Vector2(0, 0), explosionSize, explosionSize);
	explosionAnim->SetName("Explosion");
	explosionAnim->SetEnabled(false);
	explosionAnim->SetSwitchRate(1.0f / 14.0f);
	for(int i = 1; i < 15; i++) {
		std::stringstream s;
		s << "explosion" << i << ".png";
		explosionAnim->AddFrame(new Image(s.str().c_str(), explosionSize, explosionSize));
	}
	AddRenderable(explosionAnim);
	// create 3 colliders that represent the shape of the landers body and add them to the GameObject
	AddCollider(new Poly(Vector2(-7.0f, -9.0f), 6, Vector2(-1.0f, -5.5f), Vector2(1.0f, -5.5f), Vector2(1.0f, -3.0f), Vector2(-1.0f, 8.5f), Vector2(-3.0f, 4.0f), Vector2(-3.0f, 1.0f)));
	AddCollider(new Poly(Vector2(7.0f, -9.0f), 6, Vector2(-1.0f, -5.5f), Vector2(1.0f, -5.5f), Vector2(3.0f, 1.0f), Vector2(3.0f, 4.0f), Vector2(1.0f, 8.5f), Vector2(-1.0f, -3.0f)));
	AddCollider(new Poly(Vector2(0.0f, 0.0f), 9, Vector2(-3.0f, -13.0f), Vector2(0.0f, -14.5f), Vector2(3.0f, -13.0f), Vector2(6.0f, -2.0f), Vector2(6.0f, 9.0f), Vector2(1.5f, 17.0f), Vector2(-1.5f, 17.0f), Vector2(-6.0f, 9.0f), Vector2(-6.0f, -2.0f)));

	// create a new child game object to seperate the bodies colliders from the legs colliders
	GameObject * legs = new GameObject(transform->GetPosition(), transform->GetOrientation(), "Legs");
	// same as above but for the new child object
	legs->AddCollider(new Poly(Vector2(-7.0f, -16.5f), 4, Vector2(-2.0f, -1.0f), Vector2(1.0f, -1.0f), Vector2(1.0f, 1.0f), Vector2(-0.5f, 1.0f)));
	legs->AddCollider(new Poly(Vector2(7.0f, -16.5f), 4, Vector2(-1.0f, -1.0f), Vector2(2.0f, -1.0f), Vector2(0.5f, 1.0f), Vector2(-1.0f, 1.0f)));
	legs->AddCollider(new Poly(Vector2(0.0f, -16.5f), 4, Vector2(-1.5f, -1.0f), Vector2(1.5f, -1.0f), Vector2(0.5f, 1.0f), Vector2(-0.5f, 1.0f)));
	AddChild(legs); // add the legs as a child of the lander
}

Lander::~Lander() {
}

bool thrustEnabled = false;
inline void Lander::Update(const float & deltaTime) {
	GameObject::Update(deltaTime);
	if(!stopped) { // if object is still moving
		// use eulers method of 2nd order differentiation to calculate the velocity
		Vector2 acceleration = force + GRAVITY;
		// get the new velocity
		Vector2 newVelocity = velocity + acceleration * deltaTime;
		// calculate the average velocity
		velocity = (velocity + newVelocity) / 2;
		// move the Lander and its legs by the average velocity
		transform->Translate(velocity * deltaTime);
		GetChild(0)->GetTransform()->Translate(velocity * deltaTime);
		bool switchThrust = false;
		if(force.Normalized().Dot(RIGHT)) // if the forces direction faces right
			fuel -= FUEL_REDUCTION_RATE * 0.5f * deltaTime; // reduce the fuel by half the normal rate
		if(force.Normalized().Dot(UP)) {// if the forces direction faces up
			fuel -= FUEL_REDUCTION_RATE * deltaTime; // reduce the fuel by the normal rate
			if(!thrustEnabled) { // set the trust animation to switch on or off
				switchThrust = true;
			}
		}
		else { // force direction not facing up
			if(thrustEnabled) { // set the trust animation to switch on or off
				switchThrust = true;
			}
		}
		if(switchThrust) { // if the thrust animation should switch
			// switch it on or off
			thrustEnabled = !thrustEnabled; SetRenderableEnabled("Thrust", thrustEnabled);
		}
		force.Set(0.0f, 0.0f); // reset the force variable
	}
	else {
		// first disable the thrust
		if(thrustEnabled) SetRenderableEnabled("Thrust", false);
		// then disable the lander image if the object is dying
		if(dying && timeToLive < 0.5f) SetRenderableEnabled("Lander", false);
		// then disable the explosion
		if(!alive) SetRenderableEnabled("Explosion", false);
	}
	
}

void Lander::Move(Vector2 & direction) {
	Vector2 newForce = direction.Normalized();
	// set the y direction to 0 if facing down or out of fuel
	if(newForce.GetY() < 0 || fuel <= 0) newForce.SetY(0.0f);
	// add the force scaled on each axis by the relevant value
	force += Vector2(newForce.GetX() * hScaler, newForce.GetY() * vScaler);
}

void Lander::Kill(float timeToLive) {
	GameObject::Kill(timeToLive); // call te base Kill() function
	SetRenderableEnabled("Explosion", true); //enable the explosion animation
}

float Lander::GetFuel() {
	return fuel < 0 ? 0 : fuel;
}
