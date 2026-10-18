#include "Game.h"
#include "HighScore.h"
#include "Menu.h"
#include "Score.h"
#include <SFML/Audio.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")


#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#endif


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Score *scorePtr = new Score();

	sf::Music music;

	music.openFromFile("../../Resource File/music/spaceinvaders.ogg");

	music.setVolume(50);
	music.play();
	music.setLoop(true);

	GameState *current = nullptr;
	State currentState = State::NO_CHANGE;

	current = new Menu();
	currentState = State::MENU;

	while (currentState != State::EXIT)
	{
		current->handleEvents();

		if (!current->isWindowOpen())
		{
			currentState = State::EXIT;
		}
		else
		{
			currentState = current->update();
		}

		if (currentState == State::EXIT)
		{
			break;
		}

		if (currentState != State::NO_CHANGE)
		{
			switch (currentState)
			{
			case State::MENU:
				delete current;
				current = new Menu();
				break;
			case State::PLAY:
				delete current;
				current = new Game(scorePtr);
				break;
			case State::HIGHSCORE_INPUT:
				delete current;
				current = new HighScore(scorePtr);
				break;
			}
		}
		current->render();
	}

	music.stop();

	delete current;
	delete scorePtr;

	return 0;
}