#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "Tile.h"
#include "Board.h"
#include "Random.h"
#include "GameManager.h"

using namespace std;
using namespace sf;

void loadConfig(int &cols, int &rows, int &mineCount) {
    ifstream configFile("boards/config.cfg");

    if (!configFile.is_open()) {
        cout << "Could not read config";
        return;
    }

    configFile >> cols >> rows >> mineCount;

    configFile.close();
}

vector<vector<int>> getCustomMap(int &cols, int &rows, int &mineCount, string fileName) {
    string path = "boards/";
    path += fileName + ".brd";
    ifstream mapFile(path);
    vector<vector<int>> customMapArray;


    if (!mapFile.is_open()) {
        cout << "Could not read custom map file " << fileName;
        return customMapArray;
    }

    string line;
    int customMapMines = 0;
    while (getline(mapFile, line)) {
        vector<int> row;
        for (char ch : line) {
            if (ch == '1') {
                row.push_back(-1);
                customMapMines += 1;
            }
            else {
                row.push_back(0);
            }
        }

        customMapArray.push_back(row);
    }

    rows = static_cast<int>(customMapArray.size());
    cols = static_cast<int>(customMapArray[0].size());
    mineCount = customMapMines;


    return customMapArray;
}

Board generateNewGame(int &cols, int &rows, int &mineCount, string fileName, RenderWindow &window) {

    vector<vector<int>> boardArray(rows, vector<int>(cols, 0));

    if (fileName == "none") {

        loadConfig(cols, rows, mineCount);

        if (mineCount > cols * rows) {
            cout << "Can not generate board. Mines must be less than or equal to the number of tiles.";
            exit(0);
        }

        int minePositions = 0;
        while (minePositions < mineCount) {
            int x = Random::getRandomInt(0, rows - 1);
            int y = Random::getRandomInt(0, cols - 1);

            if (boardArray[x][y] == 0) {
                boardArray[x][y] = -1;
                minePositions += 1;
            }
        }
    }
    else {
        boardArray = getCustomMap(cols, rows, mineCount, fileName);
    }

    View view(FloatRect(0, 0, cols * 32.0f, (rows * 32.0f) + 100.0f));
    window.setSize(Vector2u(cols * 32, (rows * 32) + 100));
    window.setView(view);

    return Board(boardArray, rows, cols, mineCount);
}

int main()
{

    int cols, rows, mineCount;
    loadConfig(cols, rows, mineCount);

    RenderWindow window(VideoMode(cols * 32, (rows * 32) + 100), "SFML works!");

    vector<vector<int>> boardArray(rows, vector<int>(cols, 0));

    GameManager::setFlagCount(mineCount);
    Board gameBoard = generateNewGame(cols, rows, mineCount, "none", window);

    vector<vector<Tile>> boardElements;

    while (window.isOpen())
    {
        if (boardElements.empty()) {
            boardElements = gameBoard.getBoard();
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
            // Click events
            if (event.type == Event::MouseButtonPressed) {
                auto mousePosition = Mouse::getPosition(window);

                for (int i = 0; i < boardElements.size(); i++) {
                    for (int j = 0; j < boardElements[i].size(); j++) {
                        Tile &tile = boardElements[i][j];
                        Sprite clickedSprite = tile.getSprite();
                        auto spriteBounds = clickedSprite.getGlobalBounds();
                        if (spriteBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                            if (!tile.getIsClicked() && !GameManager::getGameOver()) {
                                tile.clickSprite(event.mouseButton.button, boardElements);
                                break;
                            }
                        }
                    }
                }

                if (gameBoard.getGameStatusSprite().getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {

                    gameBoard = generateNewGame(cols, rows, mineCount, "none", window);
                    boardElements.clear();
                    boardElements = gameBoard.getBoard();
                    GameManager::setGameOverVar(false);
                }


                if (gameBoard.getDebugSprite().getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    if (!GameManager::getGameOver()) {
                        GameManager::revealBombs(boardElements);
                    }
                }

                if (gameBoard.getTest1Sprite().getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    gameBoard = generateNewGame(cols, rows, mineCount, "testboard1", window);
                    boardElements.clear();
                    GameManager::setGameOverVar(false);
                }

                if (gameBoard.getTest2Sprite().getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    gameBoard = generateNewGame(cols, rows, mineCount, "testboard2", window);
                    boardElements.clear();
                    GameManager::setGameOverVar(false);
                }

                if (gameBoard.getTest3Sprite().getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    gameBoard = generateNewGame(cols, rows, mineCount, "testboard3", window);
                    boardElements.clear();
                    GameManager::setGameOverVar(false);
                }
            }
        }

        window.clear(Color::White);

        for (int i = 0; i < boardElements.size(); i++) {
            for (int j = 0; j < boardElements[i].size(); j++) {
                boardElements[i][j].drawTile(window);
            }
        }

        if (GameManager::getGameOver()) gameBoard.setGameStatusTexture("face_lose");
        if (GameManager::getClickedtiles() == (cols * rows) - mineCount) {
            gameBoard.setGameStatusTexture("face_win");
            GameManager::setGameOverVar(true);
            for (int i = 0; i < boardElements.size(); i++) {
                for (int j = 0; j < boardElements[i].size(); j++) {
                    if (boardElements[i][j].getIsBomb() && !boardElements[i][j].getIsFlagged()) {
                        boardElements[i][j].clickSprite(Mouse::Right, boardElements);
                    }
                }
            }
        }

        gameBoard.updateFlagCount();

        window.draw(gameBoard.getGameStatusSprite());
        window.draw(gameBoard.getTest3Sprite());
        window.draw(gameBoard.getTest2Sprite());
        window.draw(gameBoard.getTest1Sprite());
        window.draw(gameBoard.getDebugSprite());
        window.draw(gameBoard.getFlagDigitNegative());
        window.draw(gameBoard.getFlagDigit1());
        window.draw(gameBoard.getFlagDigit2());
        window.draw(gameBoard.getFlagDigit3());

        window.display();
    }

    return 0;
}