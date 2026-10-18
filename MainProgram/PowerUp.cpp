#include "PowerUp.h"

void PowerUp::moveSprite(float xPos, float yPos)
{
	sprite.move(xPos, yPos);
}

PowerUp::PowerUp(float xPos, float yPos, float speed, std::string textureString)
	:speed(speed)
{
	this->textureString = textureString;
	this->texture.loadFromFile(textureString);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(xPos, yPos);
}

PowerUp::PowerUp()
{
}


PowerUp::~PowerUp()
{
}

sf::FloatRect PowerUp::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void PowerUp::powerUpIsDead()
{
	if (getPowerUpIsAlive() == false)
	{
		this->sprite.setPosition(-1500.0f, -1500.0f);
	}
}

void PowerUp::setPowerUpIsAlive(bool isPowerUpAlive)
{
	this->isPowerUpAlive = isPowerUpAlive;

}

bool PowerUp::getPowerUpIsAlive()
{
	return this->isPowerUpAlive;
}

void PowerUp::fallDown()
{
	if (getPowerUpIsAlive() == true)
	{
		this->sprite.move(0, speed);

	}
}

void PowerUp::setPosition(float xPos, float yPos)
{
	sprite.setPosition(xPos, yPos);
}

bool PowerUp::hit(Shoots & theShoot) const
{
	bool didItHit = false;

	if (this->sprite.getGlobalBounds().intersects(theShoot.getGlobalBounds()))
	{
		didItHit = true;
	}
	return didItHit;
}

bool PowerUp::hit(Player & thePlayer) const
{
	bool didItHit = false;

	if (this->sprite.getGlobalBounds().intersects(thePlayer.getGlobalBounds()))
	{
		didItHit = true;
	}
	return didItHit;
}



float PowerUp::getPositionY()
{
	return this->sprite.getPosition().y;
}


void PowerUp::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
