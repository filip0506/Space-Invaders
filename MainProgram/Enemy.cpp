#include "Enemy.h"

int Enemy::direction = 1;
bool Enemy::globalMoveDownVar = false;


Enemy::Enemy (float xPos, float yPos, float speed, std::string textureString)
	:Character(xPos, yPos, speed, textureString)
{
	this->setSpeed(speed);
	this->setScale(0.5f, 0.5f);
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}


void Enemy::move(float leftBounds, float rightBounds)
{
	if (getAlive() == true)
	{
		this->moveSprite(getSpeed() * getDirection(), 0.0f);
	}
}

void Enemy::moveDown(float leftBounds, float rightBounds)
{

	if (this->getPositionX() + getGlobalBounds().width > rightBounds && getAlive() == true)
	{
		setDirection(LEFT);
		setMoveDownCheck(true);
	}
	else if (this->getPositionX() < leftBounds && getAlive() == true)
	{
		setDirection(Right);
		setMoveDownCheck(true);

	}

	if (getAlive() == true && getmoveDownCheck() == true)
	{	
		this->moveSprite(0.0f, this->getSpeed() * 10);
	}
}

bool Enemy::hit(Shoots & theShoot) const
{
	bool didItHit = false;

	if (this->getGlobalBounds().intersects(theShoot.getGlobalBounds()))
	{
		didItHit = true;
	}
	return didItHit;
}

void Enemy::setDirection(int direction)
{
	this->direction = direction;
}

int Enemy::getDirection()
{
	return this->direction;
}

void Enemy::setMoveDownCheck(bool moveDownVar)
{
	this->globalMoveDownVar = moveDownVar;
}

bool Enemy::getmoveDownCheck()
{
	return this->globalMoveDownVar;
}
