#include "AssetManager.h"
#include <soil.h>
std::unordered_map<std::string, GLuint> AssetManager::images;
AssetManager::~AssetManager() {
	for(std::unordered_map<std::string, GLuint>::iterator i = images.begin(); i != images.end(); i++) {
		glDeleteTextures(1, &(*i).second);
	}	
}

const GLuint AssetManager::LoadTexture(const std::string & file) {
	if(images.count(file) == 0) images[file] = SOIL_load_OGL_texture(("Images//" + file).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);	
	return images[file];
}
