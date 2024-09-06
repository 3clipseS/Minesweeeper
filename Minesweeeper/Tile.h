#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using namespace sf;

class Tile {
private:
	Texture unClickedTexture;
	Texture clickedTexture;
	Texture flagTexture;
	Texture bombTexture;
	Texture nearbyTexture;
	Sprite sprite;
	Sprite flagSprite;
	Sprite bombSprite;
	Sprite nearbySprite;
	Vector2f position;
	int nearbyMines;
	int x, y;
	bool isClicked = false;
	bool isFlagged = false;
	bool isBomb;
public:
	Tile();
	Tile(Vector2f position, bool isBomb, int nearbyMines, int x, int y);
	Sprite getSprite();
	Sprite getBombSprite();
	void drawTile(RenderWindow &window);
	void clickSprite(Mouse::Button button, vector<vector<Tile>> &boardArray);
	void revealNearby(vector<vector<Tile>> &boardArray) const;
	bool getIsClicked() const;
	void setIsClicked(bool value);
	bool hasNearbyBombs() const;
	bool getIsBomb() const;
	bool getIsFlagged() const;
};



#endif