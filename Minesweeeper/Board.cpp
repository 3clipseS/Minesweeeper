#include "Board.h"
#include "TextureManager.h"

Board::Board(vector<vector<int>>& array, int rows, int cols, int mineCount) : rows(rows), cols(cols), mineCount(mineCount) {

	const int offsets[8][2] = { {-1,-1}, {-1,0}, {-1, 1}, {0, -1}, {0,1}, {1,-1}, {1,0}, {1,1} };

	boardArray.resize(rows, vector<Tile>(cols));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bool isBomb = (array[i][j] == -1);
			int nearbyMines = 0;

			if (!isBomb) {
				for (const auto& offset : offsets) {
					int offsetX = i + offset[0];
					int offsetY = j + offset[1];

					if (offsetX >= 0 && offsetX < rows && offsetY >= 0 && offsetY < cols && array[offsetX][offsetY] == -1) {
						nearbyMines += 1;
					}
				}
			}

			boardArray[i][j] = Tile(Vector2f(j * 32.0f, i * 32.0f), isBomb, nearbyMines, i, j);
		}
	}

	gameStatus = Sprite(TextureManager::getTexture("face_happy"));
	gameStatus.setPosition(((cols * 32.0f) / 2.0f) - 32.0f, rows * 32.0f);

	debug = Sprite(TextureManager::getTexture("debug"));
	debug.setPosition(gameStatus.getPosition().x + 128.0f, rows * 32.0f);

	test1 = Sprite(TextureManager::getTexture("test_1"));
	test1.setPosition(debug.getPosition().x + 64.0f, rows * 32.0f);

	test2 = Sprite(TextureManager::getTexture("test_2"));
	test2.setPosition(test1.getPosition().x + 64.0f, rows * 32.0f);

	test3 = Sprite(TextureManager::getTexture("test_3"));
	test3.setPosition(test2.getPosition().x + 64.0f, rows * 32.0f);

	GameManager::setFlagCount(mineCount);

	updateFlagCount();

	GameManager::setGameOverVar(false);
	GameManager::setDebugToggle(false);
	GameManager::setClickedTiles(0);

}

vector<vector<Tile>> Board::getBoard() {
	return boardArray;
}

void Board::revealTiles(int x, int y) {
	const int mooreOffsets[8][2] = { {-1,-1}, {-1,0}, {-1, 1}, {0, -1}, {0,1}, {1,-1}, {1,0}, {1,1} };


	for (const auto& offset : mooreOffsets) {
		int offsetX = x + offset[0];
		int offsetY = y + offset[1];

		if (offsetX >= 0 && offsetX < rows && offsetY >= 0 && offsetY < cols) {
			if (boardArray[offsetX][offsetY].getIsClicked()) continue;

			if (boardArray[offsetX][offsetY].getIsBomb()) continue;

			boardArray[offsetX][offsetY].clickSprite(Mouse::Left, boardArray);
		}
	}
}

Sprite Board::getGameStatusSprite() const {
	return gameStatus;
}

void Board::setGameStatusTexture(string textureName) {
	gameStatus.setTexture(TextureManager::getTexture(textureName));
}

Sprite Board::getTest3Sprite() const {
	return test3;
}

Sprite Board::getTest2Sprite() const {
	return test2;
}

Sprite Board::getTest1Sprite() const {
	return test1;
}

Sprite Board::getDebugSprite() const {
	return debug;
}

Sprite Board::getFlagDigitNegative() const {
	return flagdigitnegative;
}
Sprite Board::getFlagDigit1() const {
	return flagdigit1;
}

Sprite Board::getFlagDigit2() const {
	return flagdigit2;
}

Sprite Board::getFlagDigit3() const {
	return flagdigit3;
}

void Board::updateFlagCount() {

	int currentMineCount = GameManager::getFlagCount();

	if (currentMineCount > 999 || currentMineCount < -99) return;

	bool isNegative = false;
	if (currentMineCount < 0) {
		isNegative = true;
		currentMineCount *= -1;
	}

	int flagCountInt3 = currentMineCount < 10 ? currentMineCount : currentMineCount % 10;

	currentMineCount = static_cast<int>(floor(currentMineCount / 10));
	int flagCountInt2 =  currentMineCount % 10;
	currentMineCount = static_cast<int>(floor(currentMineCount / 10));

	int flagCountInt1 = currentMineCount;

	if (isNegative) {
		flagdigitnegative = Sprite(TextureManager::getTexture("digits"));
		flagdigitnegative.setTextureRect(sf::IntRect(210, 0, 21, 32));
		flagdigitnegative.setPosition(0, rows * 32.0f);
	}
	else {
		flagdigitnegative.setTexture(Texture());
	}

	flagdigit1 = Sprite(TextureManager::getTexture("digits"));
	flagdigit1.setTextureRect(sf::IntRect(21 * flagCountInt1, 0, 21, 32));
	flagdigit1.setPosition(0 + 21.0f, rows * 32.0f);

	flagdigit2 = Sprite(TextureManager::getTexture("digits"));
	flagdigit2.setTextureRect(sf::IntRect(21 * flagCountInt2, 0, 21, 32));
	flagdigit2.setPosition(flagdigit1.getPosition().x + 21.0f, rows * 32.0f);

	flagdigit3 = Sprite(TextureManager::getTexture("digits"));
	flagdigit3.setTextureRect(sf::IntRect(21 * flagCountInt3, 0, 21, 32));
	flagdigit3.setPosition(flagdigit2.getPosition().x + 21.0f, rows * 32.0f);
}

