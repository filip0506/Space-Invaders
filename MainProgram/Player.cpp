#include "Player.h"
#include "Shoots.h"
#include <iostream>

Player::Player(float xPos, float yPos, float speed, std::string textureString)
	:Character( xPos,  yPos, speed, textureString)
{
	this->setSpeed(speed);
	this->setHp(3);
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::move(float leftBounds, float rightBounds)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->moveSprite(-this->getSpeed(), 0.0f);
		if (this->getPositionX() < leftBounds)
		{
			this->setPosition(leftBounds, this->getPositionY());
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->moveSprite(this->getSpeed(),0.0f);

		if (this->getPositionX() > rightBounds - 50)
		{
			this->setPosition(rightBounds - 50, this->getPositionY());
		}
	}
	
}

bool Player::hit(Enemy & theEnemy) const
{
	bool didItHit = false;

	if (this->getGlobalBounds().intersects(theEnemy.getGlobalBounds()))
	{
		didItHit = true;
	}
	return didItHit;


}

void Player::setRateOfFire(float rateOfFire)
{
	this->rateOfFire = rateOfFire;
}

float Player::getRateOfFire()
{
	return this->rateOfFire;
}


void Player::setDamage(int damage)
{
	this->damage = damage;
}

int Player::getDamage()
{
	return this->damage;
}


