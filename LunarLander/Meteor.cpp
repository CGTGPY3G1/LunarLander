#include "Meteor.h"
#include "Transform.h"
#include <string>
#include<sstream>
#include "Animation.h"
#include "Polygon.h"
#include "MyMath.h"
#include "Random.h"
Meteor::Meteor(const Vector2 & position, Vector2 & orientation, Vector2 & velocity) : GameObject(position, orientation) {
	this->velocity = velocity;
	// gwt a pseudorandom rotation speed
	this->rotationSpeed = Random::RandomFloat(-MyMath::TAU(), MyMath::TAU());
	// add the meteor image to the GameObject
	AddRenderable((new Image("meteor.png", 32, 32))->SetName("Meteor"));
	float explosionSize = 100.0f;
	// create a new animation with the specified width and height
	Animation *explosionAnim = new Animation(Vector2(0, 0), explosionSize, explosionSize);
	explosionAnim->SetName("Explosion"); // name the animation
	explosionAnim->SetEnabled(false); // set it as disabled
	explosionAnim->SetSwitchRate(1.0f / 14.0f); // set the frame switch rate in seconds
	for(int i = 1; i < 15; i++) { // load each frame and add them to the animation
		std::stringstream s;
		s << "explosion" << i << ".png";
		explosionAnim->AddFrame(new Image(s.str().c_str(), explosionSize, explosionSize));
	}
	AddRenderable(explosionAnim); // add the animation to the GameObject	
	// create colliders for the meteor
	std::vector<Vector2> colData = { Vector2(-6.0f, -14.0f), Vector2(9.0f, -14.0f), Vector2(11.0f, -9.0f), Vector2(3.0f, 11.0f), Vector2(-7.0f, 10.0f), Vector2(-15.0f, 5.0f), Vector2(-16.0f, -1.0f), Vector2(-9.0f, -11.0f) };
	Shape * collider1 = new Poly(Vector2(0.0f, -0.0f), colData);
	colData = { Vector2(11.0f, -9.0f), Vector2(15.0f, -5.0f), Vector2(15.0f, 0.0f), Vector2(13.0f, 9.0f), Vector2(8.0f, 13.0f), Vector2(6.0f, 13.0f), Vector2(3.0f, 11.0f) };
	Shape * collider2 = new Poly(Vector2(0.0f, -0.0f), colData);
	AddCollider(collider1); AddCollider(collider2); // add the colliders to the meateor
}

Meteor::~Meteor() {

}

void Meteor::Update(const float & deltaTime) {
	// update the base GameObject
	GameObject::Update(deltaTime);
	if(!stopped) {
		// move and rotate the meteor
		transform->Translate(velocity * deltaTime);
		transform->Rotate(rotationSpeed * deltaTime);
	}
	else {
		if(dying && timeToLive < 0.5f) // disable the meteor image
			SetRenderableEnabled("Meteor", false);
		if(!alive) // disable the explosion animation
			SetRenderableEnabled("Explosion", false);
	}
}


void Meteor::Kill(float timeToLive) {
	GameObject::Kill(timeToLive); // call te base Kill() function
	SetRenderableEnabled("Explosion", true); //enable the explosion animation
}