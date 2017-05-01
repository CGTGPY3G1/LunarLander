#include "GameObject.h"
#include "Renderable.h"
#include "Transform.h"
int GameObject::obId = 0;
int GameObject::NewObjectID() {
	return ++obId;
}

GameObject::GameObject(const Vector2 & position, Vector2 & orientation) {
	// create a new transform at the specified position in the specified orientation 
	transform = new Transform(position, orientation);
	// get a new object id and set the objects name to it
	objectId = NewObjectID();
	name = objectId;
}

GameObject::GameObject(const Vector2 & position, Vector2 & orientation, const std::string & name) {
	// create a new transform at the specified position in the specified orientation 
	transform = new Transform(position, orientation);
	objectId = NewObjectID();
	this->name = name;
}

GameObject::~GameObject() {
	// free the memory allocated by this object
	for(std::vector<Renderable*>::iterator i = renderables.begin(); i != renderables.end(); ++i) {
		delete * i;
	}
	renderables.clear();
	for(std::vector<Shape*>::iterator i = colliders.begin(); i != colliders.end(); ++i) {
		delete * i;
	}
	colliders.clear();
	// don't delete the  objects parent just set it to null
	parent = NULL;
	for(std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		delete * i;
	}
	children.clear();
	delete transform;
}

Transform * GameObject::GetTransform() {
	return transform;
}

void GameObject::AddRenderable(Renderable * toAdd) {
	renderables.push_back(toAdd);
}

Renderable * GameObject::GetRenderable(char * name) {
	if(renderables.size() > 0) {
		std::vector<Renderable*>::iterator i = renderables.begin();
		while(i != renderables.end()) {
			// if the renderables name matches the specified name
			if(std::strcmp((*i)->GetName().c_str(), name) == 0) {
				return (*i);
			}
			i++;
		}
	}
	return NULL;
}

void GameObject::AddCollider(Shape * toAdd) {
	colliders.push_back(toAdd);
}

std::vector<Shape*> GameObject::GetColliders() {
	return colliders;
}

std::string GameObject::GetName() {
	return name;
}

void GameObject::SetName(const char * name) {
	this->name = name;
}

GameObject * GameObject::GetParent() {
	return parent;
}

void GameObject::SetParent(GameObject * parent) {
	this->parent = parent;
}

void GameObject::AddChild(GameObject * toAdd) {
	toAdd->SetParent(this);
	children.push_back(toAdd);
}

int GameObject::GetNoOfChildren() {
	return children.size();
}

GameObject * GameObject::GetChild(const unsigned int & index) {
	GameObject * toReturn = NULL;
	if(index < GetNoOfChildren())
		toReturn = children[index];
	return toReturn;
}

bool GameObject::SetRenderableEnabled(char * name, const bool & activate) {
	if(renderables.size() > 0) {
		std::vector<Renderable*>::iterator i = renderables.begin();
		while(i != renderables.end()) {
			if(std::strcmp((*i)->GetName().c_str(), name) == 0) {
				(*i)->SetEnabled(activate);
				return true;
			}
			i++;
		}
	}
	return false;
}

bool GameObject::SetColliderEnabled(char * name, const bool & activate) {
	if(colliders.size() > 0) {
		std::vector<Shape*>::iterator i = colliders.begin();
		while(i != colliders.end()) {
			if(std::strcmp((*i)->GetName().c_str(), name) == 0) {
				(*i)->SetEnabled(activate);
				return true;
			}
			i++;
		}
	}
	return false;
}

bool GameObject::operator == (GameObject & other) {
	return objectId == other.objectId;
}

void GameObject::Kill(float timeToLive) {
	if(alive) {
		dying = true;
		stopped = true;
		this->timeToLive = timeToLive;
	}
}

bool GameObject::GetStopped() {
	return stopped;
}

void GameObject::SetStopped(const bool & stopped) {
	this->stopped = stopped;
}

bool GameObject::GetAlive() {
	return alive;
}

void GameObject::SetAlive(const bool & alive) {
	this->alive = alive;
}

Vector2 GameObject::GetVelocity() {
	return velocity;
}

void GameObject::Draw() {
	if(renderables.size() > 0) {
		Vector2 position = transform->GetPosition(); float rotation = transform->GetOrientation().AngleInRadians();
		// draw all of the objects renderables
		std::vector<Renderable*>::iterator i = renderables.begin();
		while(i != renderables.end()) {
			if((*i)->GetEnabled())
				(*i)->Draw(position, rotation);
			i++;
		}
	}
	// pass draw command to the objects children
	int noOfChildren = GetNoOfChildren();
	for(int i = 0; i < noOfChildren; i++) {
		children[i]->Draw();
	}
}

void GameObject::Update(const float & deltaTime) {
	if(dying) {
		if(timeToLive > 0)
			timeToLive -= deltaTime;
		else {
			alive = false;
			dying = false;
		}
	}
	if(renderables.size() > 0) {
		// updates the objects renderables
		// will only affect animations
		std::vector<Renderable*>::iterator i = renderables.begin();
		while(i != renderables.end()) {
			if((*i)->GetEnabled())
				(*i)->Update(deltaTime);
			i++;
		}
	}
}

// base move function, actual movement should 
// be handled in derived classes
void GameObject::Move(Vector2 & direction) {
	int noOfChildren = GetNoOfChildren();
	for(int i = 0; i < noOfChildren; i++) {
		children[i]->Move(direction);
	}
}
