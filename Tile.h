#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
class Tile
{
	sf::Sprite hiddenTile;
	sf::Sprite revealedTile;
	sf::Sprite flag;
	sf::Sprite mine;
	sf::Sprite Icon;
	sf::Sprite Negative;
	sf::Sprite firstValue;
	sf::Sprite secondValue;
	sf::Sprite thirdValue;
	sf::Sprite number;

	bool tileRevealed;
	bool flagAdded;
	bool mineHere;
	bool restartFace;
	bool digits;
	bool debug;
	bool test1;
	bool test2;
	bool test3;
	bool debugMode;
	bool gameLost;
	bool gameWon;
	bool negativeValue = false;
	bool adjacentMineNumber = false;

	int DigitConversion(char value);
public:
	Tile();
	Tile(string fileName, float xPosition, float yPosition);
	void SetPosition(float xPosition, float yPosition);
	int GetPositionX();
	int GetPositionY();
	void Draw(sf::RenderWindow& window);
	void RevealTile(int width, int rows);
	bool TileRevealed();
	void AddFlag();
	bool CheckForFlag();
	void AddMine();
	void RemoveMine();
	bool MineExistance();
	void RestartGame();
	void DebugMode();
	bool CheckLostGameStatus();
	bool CheckWonGameStatus();
	void GameLost();
	void GameWon(int width, int rows);
	void SetDigitsValue(char value, int i, int size);
	void AdjacentMineNumber(string fileName);
	bool MineNumber();
	sf::FloatRect GetBounds(string boundType);
};

