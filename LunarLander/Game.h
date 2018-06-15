#pragma once
#include "GameObject.h"
#include <vector>
#include <string>

class Game {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Game"/> class.
	/// </summary>
	/// <param name="width">The world width.</param>
	/// <param name="height">The world height.</param>
	Game(const float & worldWidth = 800, const float & worldHeight = 600);
	~Game();
	/// <summary>
	/// Displays this instance.
	/// </summary>
	void Display();
	/// <summary>
	/// Updates the the game by the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	void Update(const float & deltaTime);
	/// <summary>
	/// records special key releases.
	/// </summary>
	/// <param name="key">The key.</param>
	/// <param name="x">The x locaion of the mouse.</param>
	/// <param name="y">The y locaion of the mouse.</param>
	static void SpecialKeyUp(int key, int x, int y);
	/// <summary>
	/// records special key presses.
	/// </summary>
	/// <param name="key">The key.</param>
	/// <param name="x">The x locaion of the mouse.</param>
	/// <param name="y">The y locaion of the mouse.</param>
	static void SpecialKeyDown(int key, int x, int y);
private:
	/// <summary>
	/// Prints a string.
	/// </summary>
	/// <param name="x">The x location.</param>
	/// <param name="y">The y location.</param>
	/// <param name="scaleX">The texts x scale.</param>
	/// <param name="scaleY">The texts y scale.</param>
	/// <param name="toPrint">To string print.</param>
	/// <param name="r">The amount of red in the colour.</param>
	/// <param name="g">The amount of green in the colour.</param>
	/// <param name="b">The amount of blue in the colour.</param>
	/// <param name="alignment">The alignment.</param>
	void PrintString(float x, float y, float scaleX, float scaleY, std::string toPrint, float r, float g, float b, int alignment);
	/// <summary>
	/// converts the current attempt time to a string
	/// </summary>
	/// <param name="precision">The decimal precision of the returned string.</param>
	/// <returns>the current attemp time as a string</returns>
	std::string TimeAsString(int precision);
	/// <summary>
	/// Prints info to the screen.
	/// </summary>
	void PrintHUD();
	/// <summary>
	/// Sets up a new attempt.
	/// </summary>
	void SetUp();
	/// <summary>
	/// Creates a new meteor.
	/// </summary>
	void CreateMeteor();
	/// <summary>
	/// free the memory allocated to the objects
	/// </summary>
	void CleanUp();
	/// <summary>
	/// called when the lander crashes or lands
	/// </summary>
	/// <param name="landed">true if the lander landed successfully, lse false.</param>
	void EndAttempt(const bool & landed);
	/// <summary>
	/// Draws a rectangle.
	/// </summary>
	/// <param name="position">The centre position.</param>
	/// <param name="dimensions">The dimensions of the rectangle.</param>
	/// <param name="r">The amount of red in the colour.</param>
	/// <param name="g">The amount of green in the colour.</param>
	/// <param name="b">The amount of blue in the colour.</param>
	void DrawRect(Vector2 position, Vector2 dimensions, float r, float g, float b);
	/// <summary>
	/// Determine wether or not a key is being pressed.
	/// </summary>
	/// <param name="key">The key.</param>
	/// <returns>True if key is currently pressed</returns>
	bool GetKey(unsigned int key);
	/// <summary>
	/// fills the oldKeyStates array with the values of the newKeyStates.
	/// </summary>
	void UpdateKeys();
	std::vector<GameObject*> backgroundObjects;
	GameObject * lander = nullptr, * ground = nullptr;
	bool gameOver = true, success = false;
	float playTime = 0, meteorTimer = 1, width = 800.0f, height = 600.0f;
	int tryCount = 0, landCount = 0, crashCount = 0;
	
};
