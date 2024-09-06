#include "GameManager.h"

bool GameManager::gameOver = false;
bool GameManager::debugToggle = false;
unsigned int GameManager::clickedTiles = 0;
unsigned int GameManager::flagCount = 0;


bool GameManager::getGameOver() {
	return gameOver;
}

void GameManager::setGameOver(vector<vector<Tile>>& boardArray) {

	gameOver = true;

	for (int i = 0; i < boardArray.size(); i++) {
		for (int j = 0; j < boardArray[i].size(); j++) {
			if (boardArray[i][j].getIsBomb()) {
				boardArray[i][j].clickSprite(Mouse::Left, boardArray);
			}
		}
	}
}

void GameManager::setGameOverVar(bool value) {
	gameOver = value;
}

void GameManager::revealBombs(vector<vector<Tile>>& boardArray) {

	if (debugToggle) {
		debugToggle = false;
		for (int i = 0; i < boardArray.size(); i++) {
			for (int j = 0; j < boardArray[i].size(); j++) {
				if (boardArray[i][j].getIsBomb()) {
					boardArray[i][j].getBombSprite().setTexture(Texture());
					boardArray[i][j].getSprite().setTexture(TextureManager::getTexture("tile_hidden"));
					boardArray[i][j].setIsClicked(false);
				}
			}
		}
	}

	else {
		debugToggle = true;
		for (int i = 0; i < boardArray.size(); i++) {
			for (int j = 0; j < boardArray[i].size(); j++) {
				if (boardArray[i][j].getIsBomb()) {
					boardArray[i][j].clickSprite(Mouse::Left, boardArray);
				}
			}
		}

		gameOver = false;
	}
}

unsigned int GameManager::getClickedtiles() {
	return clickedTiles;
}

void GameManager::addClickedTiles(int value) {
	clickedTiles += value;
}

void GameManager::setClickedTiles(unsigned int value) {
	clickedTiles = value;
}

unsigned int GameManager::getFlagCount() {
	return flagCount;
}

void GameManager::setFlagCount(int value) {
	flagCount = value;
}
void GameManager::addFlagCount(int value) {
	flagCount += value;
}

void GameManager::setDebugToggle(bool value) {
	debugToggle = value;
}

bool GameManager::getDebugToggle() {
	return debugToggle;
}
