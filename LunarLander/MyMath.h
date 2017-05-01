#pragma once
class MyMath
{
public:
	/// <summary>
	/// returns pi.
	/// </summary>
	/// <returns>pi</returns>
	static float PI();
	/// <summary>
	/// returns 2 * pi.
	/// </summary>
	/// <returns>2 * pi</returns>
	static float TAU();
	/// <summary>
	/// the conversion ration form radians to degrees.
	/// </summary>
	/// <returns>the conversion ration form radians to degrees</returns>
	static float RadiansToDegrees();
	/// <summary>
	/// the conversion ration form degrees to radians.
	/// </summary>
	/// <returns>the conversion ration form degrees to radians</returns>
	static float DegreesToRadians();
};