#include "GameState.h"

GameState::GameState(std::string title)
	:window(sf::VideoMode(900, 800), title)
{
}

GameState::~GameState()
{
}
