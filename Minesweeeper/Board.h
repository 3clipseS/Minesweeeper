#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Tile.h"
#include "GameManager.h"

using namespace std;
using namespace sf;

class Board {
private:
	vector<vector<Tile>> boardArray;
	int rows;
	int cols;
	int mineCount;
	Sprite gameStatus;
	Sprite debug;
	Sprite test1;
	Sprite test2;
	Sprite test3;
	Sprite flagdigitnegative;
	Sprite flagdigit1;
	Sprite flagdigit2;
	Sprite flagdigit3;
public:
	Board(vector<vector<int>> &array, int rows, int cols, int mineCount);
	vector<vector<Tile>> getBoard();
	void revealTiles(int x, int y);
	Sprite getGameStatusSprite() const;
	void setGameStatusTexture(string textureName);
	Sprite getTest3Sprite() const;
	Sprite getTest2Sprite() const;
	Sprite getTest1Sprite() const;
	Sprite getDebugSprite() const;
	Sprite getFlagDigitNegative() const;
	Sprite getFlagDigit1() const;
	Sprite getFlagDigit2() const;
	Sprite getFlagDigit3() const;
	void updateFlagCount();
};



#endif