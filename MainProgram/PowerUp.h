#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Shoots.h"
#include <string>
class PowerUp: public sf::Drawable
{
private:
	float speed = 1.0f;
	bool isPowerUpAlive = false;
	std::string textureString;
	sf::Texture texture;
	sf::Sprite sprite;

protected:

	void moveSprite(float xPos, float yPos);

public:
	PowerUp(float xPos, float yPos, float speed, std::string textureString);

	PowerUp();

	virtual~PowerUp() = 0;

	void powerUpIsDead();
	void setPowerUpIsAlive(bool isPowerUpAlive);
	bool getPowerUpIsAlive();

	float getPositionY();
	void setPosition(float xPos, float yPos);

	void fallDown();

	sf::FloatRect getGlobalBounds() const;
	
	bool hit(Shoots & theShoot) const;
	bool hit(Player &thePlayer) const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

