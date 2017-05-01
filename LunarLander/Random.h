#pragma once
class Random {
public:
	~Random();
	/// <summary>
	/// Get a radom integer.
	/// </summary>
	/// <param name="max">the maximum value (exclusive)</param>
	/// <returns>a value between 0 (inclusive) and max (exclusive).</returns>
	static int RandomInt(unsigned int max);
	/// <summary>
	/// Get a radom integer.
	/// </summary>
	/// <param name="min">the minimum value (inclusive)</param>
	/// <param name="max">the maximum value (exclusive)</param>
	/// <returns>a value between min (inclusive) and max (exclusi
	/// <summary>
	/// Get a radom float.
	/// </summary>
	/// <param name="max">the maximum value (exclusive)</param>
	/// <returns>a value between 0 (inclusive) and max (exclusive).</returns>ve).</returns>
	static int RandomInt(unsigned int min, unsigned int max);
	static float RandomFloat(const float & max);
	/// <summary>
	/// Get a radom float.
	/// </summary>
	/// <param name="min">the minimum value (inclusive)</param>
	/// <param name="max">the maximum value (exclusive)</param>
	/// <returns>a value between min (inclusive) and max (exclusive).</returns>
	static float RandomFloat(const float & min, const float & max);
	/// <summary>
	/// Get a radom boolean.
	/// </summary>
	/// <returns>a radom boolean</returns>
	static bool RandomBool();
private:
	/// <summary>
	/// Seeds this random generator.
	/// </summary>
	static void Seed();
	// used to determine if the generator has been seeded
	static bool initialised;
};
