#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
#include "GameManager.h"

Tile::Tile() : position(0, 0), isBomb(false), nearbyMines(0), x(0), y(0), isClicked(false), isFlagged(false) {}

Tile::Tile(Vector2f position, bool isBomb, int nearbyMines, int x, int y) : position(position), isBomb(isBomb), nearbyMines(nearbyMines), x(x), y(y), isClicked(false), isFlagged(false) {

	unClickedTexture = TextureManager::getTexture("tile_hidden");
	flagTexture = TextureManager::getTexture("flag");
	sprite.setPosition(position);
	clickedTexture = TextureManager::getTexture("tile_revealed");
	bombTexture = TextureManager::getTexture("mine");

	if (nearbyMines != 0 ) {
		nearbyTexture = TextureManager::getTexture("number_" + to_string(nearbyMines));
	}

}

Sprite Tile::getSprite() {
	return sprite;
}

Sprite Tile::getBombSprite() {
	return bombSprite;
}

void Tile::drawTile(RenderWindow& window) {
	window.draw(sprite);

	if (nearbyMines != 0 && isClicked) {
		window.draw(nearbySprite);
	}


	if (!isClicked) {
		sprite.setTexture(unClickedTexture);
	}

	if (isFlagged && !isClicked) {
		window.draw(flagSprite);
	}

	if (isBomb && isClicked || GameManager::getDebugToggle() || GameManager::getGameOver()) {
		window.draw(bombSprite);
	}

}

void Tile::clickSprite(Mouse::Button button, vector<vector<Tile>> &boardArray) {

	if (isClicked) return;

	if (button == Mouse::Left) {

		if (isFlagged || GameManager::getGameOver()) {
			bombSprite.setTexture(bombTexture);
			bombSprite.setPosition(getSprite().getPosition());
			return;
		}

		isClicked = true;
		sprite.setTexture(clickedTexture);

		if (isBomb) {
			bombSprite.setTexture(bombTexture);
			bombSprite.setPosition(getSprite().getPosition());
			GameManager::setGameOver(boardArray);
		}
		else {
			GameManager::addClickedTiles(1);
			if (nearbyMines == 0) {
				revealNearby(boardArray);
			}

			else {
				nearbySprite.setTexture(nearbyTexture);
				nearbySprite.setPosition(getSprite().getPosition());
			}
		}
	}

	else if (button == Mouse::Right) {
		if (isClicked) return;

		if (isFlagged) {
			flagSprite.setTexture(Texture());
			isFlagged = false;
			GameManager::addFlagCount(1);
		}
		else {
			flagSprite.setTexture(flagTexture);
			flagSprite.setPosition(getSprite().getPosition());
			isFlagged = true;
			GameManager::addFlagCount(-1);
		}
	}
}

bool Tile::getIsClicked() const {
	return isClicked;
}

void Tile::setIsClicked(bool value) {
	isClicked = value;
}

bool Tile::hasNearbyBombs() const {
	return (nearbyMines != 0);
}

bool Tile::getIsBomb() const {
	return isBomb;
}

bool Tile::getIsFlagged() const {
	return isFlagged;
}

void Tile::revealNearby(vector<vector<Tile>> &boardArray) const{
	const int mooreOffsets[8][2] = { {-1,-1}, {-1,0}, {-1, 1}, {0, -1}, {0,1}, {1,-1}, {1,0}, {1,1} };

	size_t rows = boardArray.size();
	size_t cols = boardArray[0].size();

	for (const auto& offset : mooreOffsets) {
		int offsetX = x + offset[0];
		int offsetY = y + offset[1];

		if (offsetX >= 0 && offsetX < rows && offsetY >= 0 && offsetY < cols) {
			Tile& adjacentTile = boardArray[offsetX][offsetY];

			if (!adjacentTile.getIsClicked() && !adjacentTile.getIsBomb()) {
				adjacentTile.clickSprite(Mouse::Left, boardArray);
			}
		}
	}
}


