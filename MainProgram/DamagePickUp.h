#pragma once
#include "PowerUp.h"
#include "Player.h"

class DamagePickUp : public PowerUp
{
private:

	int increaseDamage = 1;

public:

	DamagePickUp(float xPos, float yPos, float speed = 1, std::string textureString = "../../Resource File/images/SpaceInvaders_Power_Up_Damage.png");

	~DamagePickUp();

	void setDamage(int increaseDamage);
	int getDamage();

};

