#include "Shoots.h"

Shoots::Shoots(float xPos, float yPos, float shootTravelSpeed)
	:shootTravelSpeed(shootTravelSpeed)
{
	this->texture.loadFromFile("../../Resource File/images/Shoot.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.5f,0.5f);

	this->sprite.setPosition(xPos, yPos);


}

Shoots::Shoots()
{
}


Shoots::~Shoots()
{
}

void Shoots::moveShoot()
{
		this->sprite.move(0.0f, -this->shootTravelSpeed);
}

float Shoots::getShootPositionY()
{
	return this->sprite.getPosition().y;

}

float Shoots::getShootPositionX()
{
	return this->sprite.getPosition().x;

}

void Shoots::setShootPosition(float xPos,float yPos)
{
	this->sprite.setPosition(xPos,yPos);

}

void Shoots::spawnShoot(float xPos, float yPos)
{
	sprite.setPosition(xPos, yPos);
}


void Shoots::setDeadOrOfSceen(bool deadOrOfSceen)
{
	this->isDeadOrOutOfScreen = deadOrOfSceen;
}

bool Shoots::getDeadOrOfSceen()
{
	return this->isDeadOrOutOfScreen;
}

sf::FloatRect Shoots::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Shoots::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

