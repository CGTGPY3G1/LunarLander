#include"MyMath.h"

float MyMath::PI() {
	return 3.1415927f;
}

float MyMath::TAU() {
	return PI() * 2;
}

float MyMath::RadiansToDegrees() {
	return 180 / PI();
}

float MyMath::DegreesToRadians() {
	return PI() / 180;
}
