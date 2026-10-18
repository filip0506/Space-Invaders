#pragma once
#include "GameState.h"
#include "Game.h"
#include <string>
#include <fstream>

class HighScore : public GameState
{
private:
	std::ofstream outFile;
	std::ifstream inFile;
	sf::Text scoreText; // visa score
	sf::Text highScoreText; // visa HighScore
	sf::Text labelText; // för instruktioner till användaren
	sf::Text text; // för att visa användarens inmatning
	sf::Font font;
	std::string name; // för att registrera användarens inmatning
	bool done;

	int playerScore;
	int scoreFromFile;

	std::string combinedTextString;
	std::string highScore;
	std::string playerHighScoreName;

public:
	HighScore(Score * scorePtr);
	virtual ~HighScore();

	void readFromFile();
	void writeToFile();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

	virtual bool isWindowOpen() override;


};
