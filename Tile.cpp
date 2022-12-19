#include "Tile.h"

Tile::Tile() {
	revealedTile.setTexture(TextureManager::GetTexture("images/tile_revealed"));
	hiddenTile.setTexture(TextureManager::GetTexture("images/tile_hidden"));
	flag.setTexture(TextureManager::GetTexture("images/flag"));
	mine.setTexture(TextureManager::GetTexture("images/mine"));
	tileRevealed = false;
	flagAdded = false;
	mineHere = false;
}

Tile::Tile(string fileName, float xPosition, float yPosition) {
	if (fileName == "face_happy") {
		Icon.setTexture(TextureManager::GetTexture("images/face_happy"));
		Icon.setPosition(xPosition, yPosition);
		restartFace = true;
	}
	else if (fileName == "digits") {
		Negative.setTexture(TextureManager::GetTexture("images/digits"));
		Negative.setTextureRect(sf::IntRect(210, 0, 21, 32));

		firstValue.setTexture(TextureManager::GetTexture("images/digits"));
		firstValue.setTextureRect(sf::IntRect(0, 0, 21, 32));

		secondValue.setTexture(TextureManager::GetTexture("images/digits"));
		secondValue.setTextureRect(sf::IntRect(0, 0, 21, 32));

		thirdValue.setTexture(TextureManager::GetTexture("images/digits"));
		thirdValue.setTextureRect(sf::IntRect(0, 0, 21, 32));

		Negative.setPosition(xPosition - 32, yPosition);
		firstValue.setPosition(xPosition, yPosition);
		secondValue.setPosition(xPosition + 32 , yPosition);
		thirdValue.setPosition(xPosition + 64, yPosition);
		digits = true;
	}
	else if (fileName == "debug") {
		Icon.setTexture(TextureManager::GetTexture("images/debug"));
		Icon.setPosition(xPosition, yPosition);
		debug = true;
	}
	else if (fileName == "test_1") {
		Icon.setTexture(TextureManager::GetTexture("images/test_1"));
		Icon.setPosition(xPosition, yPosition);
		test1 = true;
	}
	else if (fileName == "test_2") {
		Icon.setTexture(TextureManager::GetTexture("images/test_2"));
		Icon.setPosition(xPosition, yPosition);
		test1 = true;
	}
	else if (fileName == "test_3") {
		Icon.setTexture(TextureManager::GetTexture("images/test_3"));
		Icon.setPosition(xPosition, yPosition);
		test1 = true;
	}

}


void Tile::SetPosition(float xPosition, float yPosition) {
	hiddenTile.setPosition(xPosition, yPosition);
	revealedTile.setPosition(xPosition, yPosition);
	flag.setPosition(xPosition, yPosition);
	mine.setPosition(xPosition, yPosition);
}

int Tile::GetPositionX() {
	return hiddenTile.getPosition().x;
}

int Tile::GetPositionY() {
	return hiddenTile.getPosition().y;
}

void Tile::Draw(sf::RenderWindow& window) {
	if (tileRevealed == true && mineHere == true && debugMode == false) {
		window.draw(revealedTile);
		window.draw(mine);
		window.draw(Icon);
	}
	else if (tileRevealed == true && debugMode == false && adjacentMineNumber == true) {
		window.draw(revealedTile);
		window.draw(number);
	}
	else if (tileRevealed == true && debugMode == false && adjacentMineNumber == false) {
		window.draw(revealedTile);
	}
	else if (gameWon == true) {
		window.draw(revealedTile);
		window.draw(hiddenTile);
		window.draw(Icon);
		if (flagAdded == true && tileRevealed == false && mineHere == true) {
			window.draw(hiddenTile);
			window.draw(flag);
		}
		else if (flagAdded == false && tileRevealed == false && mineHere == true) {
			window.draw(hiddenTile);
			window.draw(flag);
		}
		else if (tileRevealed == true && adjacentMineNumber == true) {
			window.draw(revealedTile);
			window.draw(number);
		}
		else if (flagAdded == false && tileRevealed == true && mineHere == false && adjacentMineNumber == false) {
			window.draw(revealedTile);
		}
	}
	else if (gameLost == true) {
		window.draw(revealedTile);
		window.draw(hiddenTile);
		if (flagAdded == true && tileRevealed == false && mineHere == true) {
			window.draw(revealedTile);
			window.draw(mine);
		}
		if (flagAdded == true && tileRevealed == false && mineHere == false) {
			window.draw(hiddenTile);
			window.draw(flag);
		}
		else if (flagAdded == false && tileRevealed == false && mineHere == true) {
			window.draw(revealedTile);
			window.draw(mine);
		}
		else if (flagAdded == false && tileRevealed == true && mineHere == true) {
			window.draw(revealedTile);
			window.draw(mine);
			window.draw(Icon);
		}
		else if (tileRevealed == true && adjacentMineNumber == true) {
			window.draw(revealedTile);
			window.draw(number);
		}
		else if (flagAdded == false && tileRevealed == true && mineHere == false && adjacentMineNumber == false) {
			window.draw(revealedTile);
		}
	}
	else if (flagAdded == true && debugMode == false && tileRevealed == false) {
		window.draw(hiddenTile);
		window.draw(flag);
	}
	else if (restartFace == true) {
		window.draw(Icon);
	}
	else if (digits == true) {
		if (negativeValue == true) {
			window.draw(Negative);
		}
		window.draw(firstValue);
		window.draw(secondValue);
		window.draw(thirdValue);
	}
	else if (debug == true) {
		window.draw(Icon);
	}
	else if (test1 == true) {
		window.draw(Icon);
	}
	else if (test2 == true) {
		window.draw(Icon);
	}
	else if (test3 == true) {
		window.draw(Icon);
	}
	else if (debugMode == true && gameLost == false) {
		window.draw(revealedTile);
		window.draw(hiddenTile);
		if (flagAdded == true && tileRevealed == false && mineHere == true) {
			window.draw(hiddenTile);
			window.draw(flag);
			window.draw(mine);
		}
		else if (flagAdded == true && tileRevealed == false && mineHere == false) {
			window.draw(hiddenTile);
			window.draw(flag);
		}
		else if (flagAdded == false && tileRevealed == false && mineHere == true) {
			window.draw(hiddenTile);
			window.draw(mine);
		}
		else if (flagAdded == false && tileRevealed == true && mineHere == true) {
			window.draw(revealedTile);
			window.draw(mine);
			window.draw(Icon);
		}
		else if (tileRevealed == true && adjacentMineNumber == true) {
			window.draw(revealedTile);
			window.draw(number);
		}
		else if (flagAdded == false && tileRevealed == true && mineHere == false && adjacentMineNumber == false) {
			window.draw(revealedTile);
		}
	}
	else if (tileRevealed == false) {
		window.draw(hiddenTile);

	}
}

void Tile::RevealTile(int width, int rows) {
	if (flagAdded == false && tileRevealed == false && gameLost == false) {
		tileRevealed = true;
		if (mineHere == true) {
			Icon.setTexture(TextureManager::GetTexture("images/face_lose"));
			Icon.setPosition((width / 2), (rows * 32));
			gameLost = true;
		}
	}
}

bool Tile::TileRevealed() {
	return tileRevealed;
}

void Tile::AddFlag() {
	if (tileRevealed == false  && gameLost == false && gameWon == false) {
		flagAdded = !flagAdded;
	}
}

bool Tile::CheckForFlag() {
	return flagAdded;
}

void Tile::AddMine() {
	mineHere = true;
}

void Tile::RemoveMine() {
	mineHere = false;
}

bool Tile::MineExistance() {
	return mineHere;
}

void Tile::RestartGame() {
	tileRevealed = false;
	flagAdded = false;
	mineHere = false;
	gameLost = false;
	gameWon = false;
	negativeValue = false;
	adjacentMineNumber = false;
	Negative.setTextureRect(sf::IntRect(210, 0, 21, 32));
	firstValue.setTextureRect(sf::IntRect(0, 0, 21, 32));
	secondValue.setTextureRect(sf::IntRect(0, 0, 21, 32));
	thirdValue.setTextureRect(sf::IntRect(0, 0, 21, 32));
}

void Tile::DebugMode() {
	if (gameLost != true || gameWon != true) {
		debugMode = !debugMode;
	}
}


bool Tile::CheckLostGameStatus() {
	return gameLost;
}

void Tile::GameLost(){
	gameLost = true;
	debug = false;
}

sf::FloatRect Tile::GetBounds(string boundType) {
	if (boundType == "hidden") {
		return hiddenTile.getGlobalBounds();
	}
	else if(boundType == "restart") {
		return Icon.getGlobalBounds();
	}
	else if (boundType == "debug") {
		return Icon.getGlobalBounds();
	}
	else if (boundType == "test1") {
		return Icon.getGlobalBounds();
	}
	else if (boundType == "test2") {
		return Icon.getGlobalBounds();
	}
	else if (boundType == "test3") {
		return Icon.getGlobalBounds();
	}
	
}

void Tile::SetDigitsValue(char value, int i, int size) {
	int currentNum = 0;
	if (i == 0) {
		if (value == '-') {
			negativeValue = true;
		}
		else {
			negativeValue = false;
		}
	}
	if (negativeValue == true && value != '-') {
		if (size - 3 == i) {
			currentNum = DigitConversion(value);
			firstValue.setTextureRect(sf::IntRect(currentNum, 0, 21, 32));
		}
		else if (size - 2 == i) {
			currentNum = DigitConversion(value);
			secondValue.setTextureRect(sf::IntRect(currentNum, 0, 21, 32));
		}
		else if (size - 1 == i) {
			currentNum = DigitConversion(value);
			thirdValue.setTextureRect(sf::IntRect(currentNum, 0, 21, 32));
		}
	}
	else if (negativeValue == false && value != '-'){
		if (size - 3 == i) {
			currentNum = DigitConversion(value);
			firstValue.setTextureRect(sf::IntRect(currentNum, 0, 21, 32));
		}
		else if (size - 2 == i) {
			currentNum = DigitConversion(value);
			secondValue.setTextureRect(sf::IntRect(currentNum, 0, 21, 32));
		}
		else if (size - 1 == i) {
			currentNum = DigitConversion(value);
			thirdValue.setTextureRect(sf::IntRect(currentNum, 0, 21, 32));
		}
	}
	if (size == 1) {
		firstValue.setTextureRect(sf::IntRect(0, 0, 21, 32));
		secondValue.setTextureRect(sf::IntRect(0, 0, 21, 32));
	}
}

int Tile::DigitConversion(char value){ 
	int number = 0;
	switch (value) {
	case('0'):
		number = 0;
		break;

	case('1'):
		number = 21;
		break;

	case('2'):
		number = 42;
		break;

	case('3'):
		number = 63;
		break;

	case('4'):
		number = 84;
		break;

	case('5'):
		number = 105;
		break;

	case('6'):
		number = 126;
		break;

	case('7'):
		number = 147;
		break;

	case('8'):
		number = 168;
		break;

	case('9'):
		number = 189;
		break;
	}
	return number;
}

void Tile::AdjacentMineNumber(string fileName) {
	number.setTexture(TextureManager::GetTexture(fileName));
	number.setPosition(hiddenTile.getPosition().x, hiddenTile.getPosition().y);
	adjacentMineNumber = true;
}

bool Tile::CheckWonGameStatus()
{
	return gameWon;
}

void Tile::GameWon(int width, int rows){
	gameWon = true;
	Icon.setTexture(TextureManager::GetTexture("images/face_win"));
	Icon.setPosition((width / 2), (rows * 32));
}

bool Tile::MineNumber() {
	return adjacentMineNumber;
}