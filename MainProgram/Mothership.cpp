#include "Mothership.h"
#include "Enemy.h"

Mothership::Mothership(float xPos, float yPos, float speed, std::string textureString)
	:Enemy(xPos, yPos, speed, textureString)
{
	this->setSpeed(speed);
	this->setScale(0.5f, 0.5f);
	this->setAlive(false);
	this->setHp(2);

}

Mothership::Mothership()
{
}

Mothership::~Mothership()
{
}

void Mothership::move(float leftBounds, float rightBounds)
{
	if (getAlive() == true)
	{
		this->moveSprite(this->getSpeed() * direction, 0.0f);
		
		if (this->getPositionX() + this->getGlobalBounds().width > rightBounds)
		{
			direction = LEFT;
			
		}
		else if (this->getPositionX() < leftBounds)
		{
			direction = Right;
		
		}
	}
}

