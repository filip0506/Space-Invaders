#include "DamagePickUp.h"

DamagePickUp::DamagePickUp(float xPos, float yPos, float speed, std::string textureString)
	:PowerUp(xPos, yPos, speed, textureString)
{
}

DamagePickUp::~DamagePickUp()
{
}

void DamagePickUp::setDamage(int increaseDamage)
{

	this->increaseDamage = increaseDamage;
}

int DamagePickUp::getDamage()
{
	return this->increaseDamage;
}

