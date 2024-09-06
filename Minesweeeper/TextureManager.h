#ifndef TEXTURE_H
#define TEXTURE_H
#include <unordered_map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager {
	static unordered_map<string, Texture> textures;

public:
	static void loadTexture(const string &textureName);
	static Texture& getTexture(const string &textureName);
	static void clearTextures();
};

#endif

