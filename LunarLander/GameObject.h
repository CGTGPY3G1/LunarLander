// GameObject is the base class for all objects that will be placed in the game

#pragma once
#include <vector>
#include "Shape.h"

class Vector2;
class Transform;
class Renderable;
class GameObject {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GameObject"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="orientation">The orientation.</param>
	GameObject(const Vector2 & position, Vector2 & orientation);
	/// <summary>
	/// Initializes a new instance of the <see cref="GameObject"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="orientation">The orientation.</param>
	/// <param name="name">The name.</param>
	GameObject(const Vector2 & position, Vector2 & orientation, const std::string & name);
	/// <summary>
	/// Finalizes an instance of the <see cref="GameObject"/> class.
	/// </summary>
	virtual ~GameObject();
	/// <summary>
	/// Gets this objects Transform.
	/// </summary>
	/// <returns>the objects Transform</returns>
	Transform * GetTransform();
	/// <summary>
	/// Draws this instance.
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// Updates the object by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void Update(const float & deltaTime);
	/// <summary>
	/// Moves the object in the specified direction.
	/// </summary>
	/// <param name="amount">The movement direction.</param>
	virtual void Move(Vector2 & direction);
	/// <summary>
	/// Adds a Renderable.
	/// </summary>
	/// <param name="toAdd">The Renderable to add.</param>
	void AddRenderable(Renderable * toAdd);
	Renderable * GetRenderable(char * name);
	/// <summary>
	/// Adds a Collider.
	/// </summary>
	/// <param name="toAdd">The Collider to add.</param>
	void AddCollider(Shape * toAdd);
	/// <summary>
	/// Gets the colliders.
	/// </summary>
	/// <returns>any colliders attached to this object</returns>
	std::vector<Shape*> GetColliders();
	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <returns>The name</returns>
	std::string GetName();
	/// <summary>
	/// Sets the name.
	/// </summary>
	/// <param name="name">The name.</param>
	void SetName(const char * name);
	/// <summary>
	/// Gets the objects parent.
	/// </summary>
	/// <returns>The objects parent</returns>
	GameObject * GetParent();
	void SetParent(GameObject* parent);
	/// <summary>
	/// Adds a child.
	/// </summary>
	/// <param name="toAdd">The child to add.</param>
	void AddChild(GameObject * toAdd);
	int GetNoOfChildren();
	/// <summary>
	/// Gets the specified child.
	/// </summary>
	/// <param name="index">The index of the child.</param>
	/// <returns>the specified child</returns>
	GameObject * GetChild(const unsigned int & index);
	/// <summary>
	/// Enables a Renderable.
	/// </summary>
	/// <param name="name">The name of the Renderable.</param>
	/// <param name="activate">The activate.</param>
	/// <returns>true if successful, else false</returns>
	bool SetRenderableEnabled(char * name, const bool & activate);
	/// <summary>
	/// Enables a Collider.
	/// </summary>
	/// <param name="name">The name of the Collider.</param>
	/// <param name="activate">should the object be activated or not.</param>
	/// <returns>true if successful, else false</returns>
	bool SetColliderEnabled(char * name, const bool & activate);
	bool operator == (GameObject & other);
	/// <summary>
	/// Kills the object over the specified time to live.
	/// </summary>
	/// <param name="timeToLive">The time to live.</param>
	virtual void Kill(float timeToLive);
	/// <summary>
	/// Gets the stopped variable.
	/// </summary>
	/// <returns>True if object is stopped, else False</returns>
	bool GetStopped();
	/// <summary>
	/// Sets the stopped variable.
	/// </summary>
	/// <param name="stopped">The new value of stopped.</param>
	void SetStopped(const bool & stopped);
	/// <summary>
	/// Gets the alive variable.
	/// </summary>
	/// <returns>True if object is alive, else False</returns>
	bool GetAlive();
	/// <summary>
	/// Sets the variable.
	/// </summary>
	/// <param name="alive">The new value of alive.</param>
	void SetAlive(const bool & alive);
	/// <summary>
	/// Gets the velocity.
	/// </summary>
	/// <returns>the velocity of the object</returns>
	Vector2 GetVelocity();
protected:
	int objectId;
	Vector2 velocity;
	std::string name;
	Transform * transform;
	std::vector<Renderable*> renderables;
	std::vector<Shape*> colliders;
	GameObject * parent;
	std::vector<GameObject*> children;
	bool alive = true, dying = false, stopped = false;
	float timeToLive = 0.0f;
private:
	static int obId;
	static int NewObjectID();
};

