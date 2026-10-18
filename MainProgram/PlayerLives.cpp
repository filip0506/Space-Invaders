#include "PlayerLives.h"
#include <iostream>

PlayerLives::PlayerLives(sf::Color color,float xPos, float yPos)
{
	this->playerTexture.loadFromFile("../../Resource File/images/SpaceInvaders_Player.png");
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setPosition(xPos, yPos);
	this->playerSprite.setColor(color);
}

PlayerLives::PlayerLives()
{
}

PlayerLives::~PlayerLives()
{
}

void PlayerLives::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->playerSprite);
}
