#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class PlayerLives : public sf::Drawable
{
private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
public:
	PlayerLives(sf::Color color,float xPos, float yPos);
	PlayerLives();

	~PlayerLives();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

