#pragma once
#include <unordered_map>
#include <gl/glut.h>
#include <string>

class AssetManager {
public:
	~AssetManager();
	static const GLuint LoadTexture(const std::string & file);
private:
	static std::unordered_map<std::string, GLuint> images;
};