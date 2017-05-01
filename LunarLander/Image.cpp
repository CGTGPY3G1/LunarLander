#include "Image.h"
#include <iostream>
#include "Vector2.h"
#include "AssetManager.h"

Image::Image(const std::string & file, const float & width, const float & height) : Renderable(Vector2(0, 0), 0, width, height) {
	BuildTexture(file);
}

Image::~Image() {
}

void Image::BuildTexture(const std::string & file) {
	iD = AssetManager::LoadTexture(file);
	if(iD != 0) {	
		double halfWidth = dimensions.GetX() / 2, halfHeight = dimensions.GetY() / 2;
		// create vertices for the quad that the image will be mapped to
		vertices[0] = Vector2(-halfWidth, -halfHeight);
		vertices[1] = Vector2(halfWidth, -halfHeight);
		vertices[2] = Vector2(halfWidth, halfHeight);
		vertices[3] = Vector2(-halfWidth, halfHeight);
		glEnable(GL_TEXTURE_2D); // enable 2d textures
		glBindTexture(GL_TEXTURE_2D, iD); // bind the texture
		// then set its parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

bool Image::IsInitialized() {
	return iD != 0; // the id will only be 0 if the texture isn't initialized 
}

void Image::Draw(const Vector2 & origin, const float & rotation) {
	glBindTexture(GL_TEXTURE_2D, iD);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND); // enable blending
	glColor4d(1, 1, 1, 1);
	// draw a quad with the texture printed on to
	glBegin(GL_QUADS);
	float toRotate = rotation + this->rotation;
	Vector2 point = origin + (center + vertices[0]).RotatedInRadians(toRotate);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(point.GetX(), point.GetY());
	point = origin + (center + vertices[1]).RotatedInRadians(toRotate);
	glTexCoord2d(1.0f, 0.0f); glVertex2d(point.GetX(), point.GetY());
	point = origin + (center + vertices[2]).RotatedInRadians(toRotate);
	glTexCoord2d(1.0f, 1.0f); glVertex2d(point.GetX(), point.GetY());
	point = origin + (center + vertices[3]).RotatedInRadians(toRotate);
	glTexCoord2d(0.0f, 1.0f); glVertex2d(point.GetX(), point.GetY());
	glEnd();
}

RenderableType Image::GetType() {
	return IMAGE;
}
