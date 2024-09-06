#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include "Tile.h"
#include "TextureManager.h"

class GameManager {

	static bool gameOver;
	static bool debugToggle;
	static unsigned int clickedTiles;
	static unsigned int flagCount;

public:
	static bool getGameOver();
	static void setGameOver(vector<vector<Tile>>& boardArray);
	static void setGameOverVar(bool value);
	static void revealBombs(vector<vector<Tile>>& boardArray);
	static unsigned int getClickedtiles();
	static void addClickedTiles(int value);
	static void setClickedTiles(unsigned int value);
	static unsigned int getFlagCount();
	static void setFlagCount(int value);
	static void addFlagCount(int value);
	static void setDebugToggle(bool value);
	static bool getDebugToggle();

};

#endif

