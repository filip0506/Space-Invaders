#pragma once
#include "PowerUp.h"
#include "Player.h"

class HpPickUp : public PowerUp
{
private:

	int hp = 1;
public:

	HpPickUp(float xPos, float yPos, float speed = 1, std::string textureString = "../../Resource File/images/SpaceInvaders_Power_Up.png");

	~HpPickUp();

	void setHp(int hp);
	int getHp();
};

