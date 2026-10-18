#include "HighScore.h"
#include "Game.h"
#include <iostream>
#include <string>

HighScore::HighScore(Score * scorePtr)
	:GameState("Highscore")
{
	this->playerScore = scorePtr->getScore();
	scorePtr->setScore(0);

	highScoreText.setFont(font);
	highScoreText.setPosition(400.0f, 50.0f);
	highScoreText.setFillColor(sf::Color::Green);
	highScoreText.setCharacterSize(30);
	highScoreText.setString("");

	scoreText.setFont(font);
	scoreText.setPosition(350, 650);
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setCharacterSize(30);
	scoreText.setString("Player score: " + std::to_string(playerScore));

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	labelText.setFont(font);
	labelText.setPosition(300.0f, 700.0f);
	labelText.setFillColor(sf::Color::Green);
	labelText.setCharacterSize(30);
	labelText.setString("Input name (<enter> when done)");

	text.setFont(font);
	text.setPosition(350, 750);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(30);
	name = "";

	text.setString(name);
	done = false;


	readFromFile();

	highScoreText.setString(combinedTextString);


}

HighScore::~HighScore()
{
}

void HighScore::readFromFile()
{
	inFile.open("../../Resource File/TextFiles/HighScore.txt");

	if (inFile.is_open())
	{
		inFile >> highScore;
		while (inFile >> playerHighScoreName >> scoreFromFile)
		{
			combinedTextString = combinedTextString + playerHighScoreName + " " + std::to_string(scoreFromFile) + "\n";
		}
		combinedTextString = highScore + "\n" + combinedTextString;
	}


	inFile.close();
}

void HighScore::writeToFile()
{
	outFile.open("../../Resource File/TextFiles/HighScore.txt", std::ios::app);
	outFile << "\n" << name << " " << playerScore;
	outFile.close();
}



State HighScore::update()
{
	State state = State::NO_CHANGE;

	if (done)
	{
		state = State::MENU;
	}

	return state;
}

void HighScore::render()
{
	window.clear();
	window.draw(highScoreText);
	window.draw(labelText);
	window.draw(scoreText);
	window.draw(text);

	window.display();
}

void HighScore::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				this->done = true;

				writeToFile();
				
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					name.erase(name.length() - 1, 1);

				}
				else if (event.text.unicode >= 0 || event.text.unicode <= 25)
				{
					this->name += (char)(event.text.unicode + 65);
				}
			}
		
			
			
			text.setString(name);
		}	
	}

}

bool HighScore::isWindowOpen()
{
	return window.isOpen();
}
