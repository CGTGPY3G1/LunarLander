#pragma once
#include <gl/glut.h>
#include "Renderable.h"
class Vector2;
class Image : public Renderable {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Image"/> class.
	/// </summary>
	/// <param name="file">The file name.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	Image(const std::string & file, const float & width, const float & height);
	~Image();
	/// <summary>
	/// Builds the texture.
	/// </summary>
	/// <param name="file">The file name.</param>
	void BuildTexture(const std::string & file);
	/// <summary>
	/// Determines whether this instance is initialized.
	/// </summary>
	/// <returns>true is initialzes, else false</returns>
	bool IsInitialized();
	/// <summary>
	/// Draws the Image to the screen.
	/// </summary>
	/// <param name="origin">The origin.</param>
	/// <param name="rotation">The rotation.</param>
	void Draw(const Vector2 & origin, const float & rotation) override;
	/// <summary>
	/// Gets the Renderable Type.
	/// </summary>
	/// <returns>the RenderableType</returns>
	RenderableType GetType() override;
private:
	GLuint iD;
};

