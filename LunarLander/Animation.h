#pragma once
#include "Image.h"
#include <vector>

class Animation : public Renderable {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Animation"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	Animation(const Vector2 & position, const float & width, const float & height);
	~Animation();
	/// <summary>
	/// Draws the Animation to the screen.
	/// </summary>
	/// <param name="origin">The origin.</param>
	/// <param name="rotation">The rotation.</param>
	void Draw(const Vector2 & origin, const float & rotation) override;
	/// <summary>
	/// Adds the frame.
	/// </summary>
	/// <param name="image">The image.</param>
	void AddFrame(Image * image);
	/// <summary>
	/// Gets the switch rate.
	/// </summary>
	/// <returns>the switch rate</returns>
	float GetSwitchRate();
	/// <summary>
	/// Sets the switch rate.
	/// </summary>
	/// <param name="rate">the switch rate.</param>
	void SetSwitchRate(const float & rate);
	/// <summary>
	/// Updates the Animation by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	void Update(const float & deltaTime) override;
	/// <summary>
	/// Gets the number of frames.
	/// </summary>
	/// <returns>the number of frames</returns>
	int GetNoOfFrames();
	/// <summary>
	/// Gets the Renderable Type.
	/// </summary>
	/// <returns>the RenderableType</returns>
	RenderableType GetType() override;
private:

	/// <summary>
	/// Moves to the next frame.
	/// </summary>
	void MoveToNextFrame();
	std::vector<Image*> frames;
	float frameSwitchRate = 0.05f, switchTimer = 0;
	int currentFrame = 0;
};
