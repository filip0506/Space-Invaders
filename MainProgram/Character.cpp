#include "Character.h"
#include <string>



void Character::moveSprite(float xPos,float yPos)
{
	sprite.move(xPos, yPos);
}


Character::Character(float xPos, float yPos, float speed,std::string textureString)
{
	this->texture.loadFromFile(textureString);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(xPos, yPos);

}

Character::Character()
{
}


Character::~Character()
{
}

void Character::setHp(int hp)
{
	this->hp = hp;
}

int Character::getHp()
{
	return this->hp;
}

void Character::setSpeed(float speed)
{
	this->speed = speed;
}

float Character::getSpeed()
{
	return this->speed;
}

void Character::setPosition(float xPos, float yPos)
{
	this->sprite.setPosition(xPos, yPos);
}

float Character::getPositionY()
{
	return this->sprite.getPosition().y;
}

void Character::setScale(float xScale, float yScale)
{
	this->sprite.setScale(xScale, yScale);
}

void Character::setColor(sf::Color color)
{
	sprite.setColor(color);
}

float Character::getPositionX()
{
	return this->sprite.getPosition().x;
}

sf::FloatRect Character::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Character::setAlive(bool alive)
{
	this->alive = alive;
}

bool Character::getAlive()
{
	return this->alive;
}

void Character::isDead(float xPos, float yPos)
{
	if (getAlive() == false)
	{
		this->setPosition(xPos, yPos);
	}
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}





