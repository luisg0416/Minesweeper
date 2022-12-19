#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "TextureManager.h"
#include "Board.h"
#include "Tile.h"
#include "Random.h"
using namespace std;

void randomMines(Tile** board, int numMines, int columns, int rows);
void boardFiles(Tile** board, string fileName, float columns, float rows);
void digitCount(Tile** board, float numMines, Tile &digits, float columns, float rows);
void gameOverBoard(Tile** board, float columns, float rows);
void RevealNum(Tile** board, float columns, float rows);
void RevealTiles(Tile** board, float columns, float rows, float currentColumn, float currentRow);
void gameWonBoard(Tile** board, float columns, float rows, int numMines);

int main()
{
    ifstream inFile;
    inFile.open("boards/config.cfg");
    float value;
    unsigned int width;
    unsigned int height;
    float tileCount;
    float columns;
    float rows;
    float numMines;
    int count = 1;

    while (inFile >> value) {
        if (count == 1) {
            columns = value;
        }
        if (count == 2) {
            rows = value;
        }
        if (count == 3) {
            numMines = value;
        }
        count++;
    }
    inFile.close();

    width = columns * 32;
    height = (rows * 32) + 88;
    tileCount = columns * rows;

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    Tile** board = new Tile * [columns];
    for (int y = 0; y < columns; y++) {
        board[y] = new Tile[rows];
    }
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            Tile tile;
            board[x][y] = tile;
            board[x][y].SetPosition((x * 32), (y * 32) );
        }
    }

    Tile face("face_happy", (width / 2), (rows * 32));
    Tile digits("digits", (32), (rows * 32));
    Tile debug("debug", (width / 2) + 128, (rows * 32));
    Tile test1("test_1", (width / 2) + 192, (rows * 32));
    Tile test2("test_2", (width / 2) + 256, (rows * 32));
    Tile test3("test_3", (width / 2) + 320, (rows * 32));

    randomMines(board, numMines, columns, rows);
    RevealNum(board, columns, rows);
    digitCount(board, numMines, digits, columns, rows);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                for (int y = 0; y < rows; y++) {
                    for (int x = 0; x < columns; x++) {
                        if (board[x][y].GetBounds("hidden").contains(mousePosition)) {
                            if (board[x][y].CheckLostGameStatus() == false && board[x][y].CheckWonGameStatus() == false) {
                                board[x][y].RevealTile(width, rows);
                                RevealTiles(board, columns, rows, x, y);
                            }
                            if (board[x][y].CheckLostGameStatus() == true) {
                                gameOverBoard(board, columns, rows);
                            }
                            if (board[x][y].CheckWonGameStatus() == false) {
                                gameWonBoard(board, columns, rows, numMines);
                            }
                        }
                    }
                }
                if (face.GetBounds("restart").contains(mousePosition)) {
                    for (int y = 0; y < rows; y++) {
                        for (int x = 0; x < columns; x++) {
                            board[x][y].RestartGame();
                        }
                    }
                    randomMines(board, numMines, columns, rows);
                    digits.RestartGame();
                    RevealNum(board, columns, rows);
                    digitCount(board, numMines, digits, columns, rows);
                }
                if (debug.GetBounds("debug").contains(mousePosition)) {
                    for (int y = 0; y < rows; y++) {
                        for (int x = 0; x < columns; x++) {
                            board[x][y].DebugMode();
                        }
                    }
                }
                if (test1.GetBounds("test1").contains(mousePosition)) {
                    for (int y = 0; y < rows; y++) {
                        for (int x = 0; x < columns; x++) {
                            board[x][y].RestartGame();
                        }
                    }
                    boardFiles(board, "testboard1.brd", columns, rows);
                    digits.RestartGame();
                    RevealNum(board, columns, rows);
                    digitCount(board, numMines, digits, columns, rows);
                }
                if (test2.GetBounds("test2").contains(mousePosition)) {
                    for (int y = 0; y < rows; y++) {
                        for (int x = 0; x < columns; x++) {
                            board[x][y].RestartGame();
                        }
                    }
                    boardFiles(board, "testboard2.brd", columns, rows);
                    digits.RestartGame();
                    RevealNum(board, columns, rows);
                    digitCount(board, numMines, digits, columns, rows);
                }
                if (test3.GetBounds("test3").contains(mousePosition)) {
                    for (int y = 0; y < rows; y++) {
                        for (int x = 0; x < columns; x++) {
                            board[x][y].RestartGame();
                        }
                    }
                    boardFiles(board, "testboard3.brd", columns, rows);
                    digits.RestartGame();
                    RevealNum(board, columns, rows);
                    digitCount(board, numMines, digits, columns, rows);
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                for (int y = 0; y < rows; y++) {
                    for (int x = 0; x < columns; x++) {
                        if (board[x][y].GetBounds("hidden").contains(mousePosition)) {
                            board[x][y].AddFlag();
                            digitCount(board, numMines, digits, columns, rows);
                        }
                    }
                }
            }
        }
            window.clear();
            face.Draw(window);
            for (int y = 0; y < rows; y++) {
                for (int x = 0; x < columns; x++) {
                    board[x][y].Draw(window);
                }
            }
            debug.Draw(window);
            digits.Draw(window);
            test1.Draw(window);
            test2.Draw(window);
            test3.Draw(window);


            window.display();
    }

        for (int y = 0; y < rows; y++) {
            delete[] board[y];
        }
        delete[] board;

        TextureManager::Clear();
        return 0;
    }

void randomMines(Tile** board, int numMines, int columns, int rows) {
    for (int i = 1; i <= numMines;) {
        int RandomX = Random::Int(0, columns) * 32;
        int RandomY = Random::Int(0, rows) * 32;
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                if (RandomX == board[x][y].GetPositionX() && RandomY == board[x][y].GetPositionY() && board[x][y].MineExistance() == false) {
                    board[x][y].AddMine();
                    i++;
                }
            }
        }
    }
}

void boardFiles(Tile** board, string fileName, float columns, float rows) {
    char value;
    int count = 0;
    ifstream File;
    vector<char> testBoards;
    File.open(fileName);
    while (File >> value) {
        char num = value;
        testBoards.push_back(num);
        count++;
        if (count == 25) {
            count = 0;
        }
    }
    int i = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (testBoards[i] == '1') {
                board[x][y].AddMine();
                i++;
            }
            else {
                board[x][y].RemoveMine();
                i++;
            }
        }
    }
}

void digitCount(Tile** board, float numMines, Tile& digits, float columns, float rows) {
    int numFlags = 0;
    int numShown;
    numMines = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (board[x][y].CheckForFlag() == true) {
                numFlags++;
            }
            if (board[x][y].MineExistance() == true) {
                numMines++;
            }
        }
    }
        numShown = numMines - numFlags;
        string counter = to_string(numShown);
        for (int i = 0; i < counter.size(); i++) {
            digits.SetDigitsValue(counter[i], i, counter.size());
        }
}

void gameOverBoard(Tile** board, float columns, float rows) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            board[x][y].GameLost();
        }
    }
}

void RevealNum(Tile** board, float columns, float rows) {
    int adjacentMines = 0;
    string wordNumMines;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            adjacentMines = 0;
            if (x > 0 && y > 0) { 
                if (board[x - 1][y - 1].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (y > 0) { 
                if (board[x][y - 1].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (x < columns - 1 && y > 0) { 
                if (board[x + 1][y - 1].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (x > 0) { 
                if (board[x - 1][y].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (x < columns - 1) { 
                if (board[x + 1][y].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (x > 0 && y < rows - 1) { 
                if (board[x - 1][y + 1].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (y < rows - 1) { 
                if (board[x][y + 1].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (x < columns - 1 && y < rows - 1) { 
                if (board[x + 1][y + 1].MineExistance() == true) {
                    adjacentMines++;
                }
            }
            if (adjacentMines > 0) {
                wordNumMines = "images/number_" + to_string(adjacentMines) +".png";
                board[x][y].AdjacentMineNumber(wordNumMines);
            }
        }
    }
}

void RevealTiles(Tile** board, float columns, float rows, float currentColumn, float currentRow) {
    int x = currentColumn;
    int y = currentRow;
    if (x > 0 && y > 0 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x - 1][y - 1].MineExistance() == false && board[x - 1][y - 1].TileRevealed() == false) {
            board[x - 1][y - 1].RevealTile((x - 1), (y - 1));
            if (board[x - 1][y - 1].MineNumber() == false) {
                RevealTiles(board, columns, rows, (x - 1), (y - 1));
            }
        }
    }
    if (y > 0 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x][y - 1].MineExistance() == false && board[x][y - 1].TileRevealed() == false) {
            board[x][y - 1].RevealTile(x, (y - 1));
            if (board[x][y - 1].MineNumber() == false) {
                RevealTiles(board, columns, rows, x, (y - 1));
            }
        }
    }
    if (x < columns - 1 && y > 0 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x + 1][y - 1].MineExistance() == false && board[x + 1][y - 1].TileRevealed() == false) {
            board[x + 1][y - 1].RevealTile((x + 1), (y - 1));
            if (board[x + 1][y - 1].MineNumber() == false) {
                RevealTiles(board, columns, rows, (x + 1), (y - 1));
            }
        }
    }
    if (x > 0 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x - 1][y].MineExistance() == false && board[x - 1][y].TileRevealed() == false) {
            board[x - 1][y].RevealTile((x - 1), y);
            if (board[x - 1][y].MineNumber() == false) {
                RevealTiles(board, columns, rows, (x - 1), y);
            }
        }
    }
    if (x < columns - 1 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x + 1][y].MineExistance() == false && board[x + 1][y].TileRevealed() == false) {
            board[x + 1][y].RevealTile((x + 1), y);
            if (board[x + 1][y].MineNumber() == false) {
                RevealTiles(board, columns, rows, (x + 1), y);
            }
        }
    }
    if (x > 0 && y < rows - 1 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x - 1][y + 1].MineExistance() == false && board[x - 1][y + 1].TileRevealed() == false) {
            board[x - 1][y + 1].RevealTile((x - 1), (y + 1));
            if (board[x - 1][y + 1].MineNumber() == false) {
                RevealTiles(board, columns, rows, (x - 1), (y + 1));
            }
        }
    }
    if (y < rows - 1 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x][y + 1].MineExistance() == false && board[x][y + 1].TileRevealed() == false) {
            board[x][y + 1].RevealTile(x, (y + 1));
            if (board[x][y + 1].MineNumber() == false) {
                RevealTiles(board, columns, rows, x, (y + 1));
            }
        }
    }
    if (x < columns - 1 && y < rows - 1 && board[x][y].MineNumber() == false && board[x][y].MineExistance() == false) {
        if (board[x + 1][y + 1].MineExistance() == false && board[x + 1][y + 1].TileRevealed() == false) {
            board[x + 1][y + 1].RevealTile((x + 1), (y + 1));
            if (board[x + 1][y + 1].MineNumber() == false) {
                RevealTiles(board, columns, rows, (x + 1), (y + 1));
            }
        }
    }
}

void gameWonBoard(Tile** board, float columns, float rows, int numMines) {
    int totalTiles = columns * rows;
    numMines = 0;
    int revealedTileCount = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
           if(board[x][y].TileRevealed() == true && board[x][y].MineExistance() == false) {
               revealedTileCount++;
        }
           if (board[x][y].MineExistance() == true) {
               numMines++;
           }
    }
}
    if (revealedTileCount == totalTiles - numMines) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                board[x][y].GameWon((columns * 32) , rows);
            }
        }
    }
}