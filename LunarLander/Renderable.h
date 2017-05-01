#pragma once
#include "Vector2.h"
#include <string>
enum RenderableType {
	ANIMATION,
	IMAGE,
	SHAPE
};
class Renderable {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Renderable"/> class.
	/// </summary>
	Renderable();
	/// <summary>
	/// Initializes a new instance of the <see cref="Renderable" /> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="rotation">The rotation.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	Renderable(const Vector2 & position, const float & rotation, float width, float height);
	virtual ~Renderable();
	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns>the rotation</returns>
	float GetRotation();
	/// <summary>
	/// Sets the rotation.
	/// </summary>
	/// <param name="rotation">The rotation.</param>
	void SetRotation(const float & rotation);
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>the position</returns>
	Vector2 GetPosition();
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="position">The position.</param>
	void SetPosition(const Vector2 & position);
	/// <summary>
	/// Gets the width.
	/// </summary>
	/// <returns>the width.</returns>
	float GetWidth();
	/// <summary>
	/// Sets the width.
	/// </summary>
	/// <param name="width">The width.</param>
	void SetWidth(const float & width);
	/// <summary>
	/// Gets the height.
	/// </summary>
	/// <returns>the height.</returns>
	float GetHeight();
	/// <summary>
	/// Sets the height.
	/// </summary>
	/// <param name="height">The height.</param>
	void SetHeight(const float & height);
	/// <summary>
	/// Sets the dimensions.
	/// </summary>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	void SetDimensions(const float & width, const float & height);
	/// <summary>
	/// Sets the dimensions.
	/// </summary>
	/// <param name="dimensions">The dimensions.</param>
	void SetDimensions(const Vector2 & dimensions);
	/// <summary>
	/// Updates the Renderable by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void Update(const float & deltaTime);
	/// <summary>
	/// Draws the object that ovverrides it to the screen.
	/// </summary>
	/// <param name="origin">The origin.</param>
	/// <param name="rotation">The rotation.</param>
	virtual void Draw(const Vector2 & origin, const float & rotation) = 0;
	/// <summary>
	/// Gets the the object that ovverrides its Renderable Type.
	/// </summary>
	/// <returns>the RenderableType</returns>
	virtual RenderableType GetType() = 0;
	/// <summary>
	/// Gets the enabled variable.
	/// </summary>
	/// <returns>true is enabled, else false</returns>
	bool GetEnabled();
	/// <summary>
	/// Sets the enabled variable.
	/// </summary>
	/// <param name="enabled">wether the object should be enabled or not.</param>
	void SetEnabled(const bool & enabled);
	/// <summary>
	/// Gets the  Renderables name.
	/// </summary>
	/// <returns>The name</returns>
	std::string GetName();
	/// <summary>
	/// Sets the  Renderables name.
	/// </summary>
	/// <param name="name">The name.</param>
	Renderable * SetName(std::string name);
protected:
	Vector2 vertices[4];
	Vector2 dimensions, center;
	float rotation;
	bool enabled = true;
	std::string name = "";
};

