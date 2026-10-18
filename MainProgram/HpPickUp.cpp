#include "HpPickUp.h"

HpPickUp::HpPickUp(float xPos, float yPos, float speed, std::string textureString)
	:PowerUp(xPos,yPos,speed,textureString)
{	
}


HpPickUp::~HpPickUp()
{
}

void HpPickUp::setHp(int hp)
{

	this->hp = hp;
}

int HpPickUp::getHp()
{
	return this->hp;
}
