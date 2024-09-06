#include "TextureManager.h"


unordered_map<string, Texture> TextureManager::textures;

void TextureManager::loadTexture(const string &fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

Texture& TextureManager::getTexture(const string &textureName) {
	if (textures.find(textureName) == textures.end()) loadTexture(textureName);

	return textures[textureName];
}

void TextureManager::clearTextures() {
	textures.clear();
}