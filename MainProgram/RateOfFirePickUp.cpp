#include "RateOfFirePickUp.h"

RateOfFirePickUp::RateOfFirePickUp(float xPos, float yPos, float speed, std::string textureString)
	:PowerUp(xPos, yPos, speed, textureString)
{
}


RateOfFirePickUp::~RateOfFirePickUp()
{
}

void RateOfFirePickUp::setRateOfFire(float increaseRateOfFire)
{
	this->increaseRateOfFire = increaseRateOfFire;
}

float RateOfFirePickUp::getRateOfFire()
{
	return this->increaseRateOfFire;
}
