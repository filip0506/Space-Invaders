#pragma once
#include "PowerUp.h"
#include "Player.h"

class RateOfFirePickUp : public PowerUp
{
private:

	float increaseRateOfFire = 0.1f;

public:

	RateOfFirePickUp(float xPos, float yPos, float speed = 1, std::string textureString = "../../Resource File/images/SpaceInvaders_Power_Up_RateOfFire.png");

	~RateOfFirePickUp();

	void setRateOfFire(float increaseRateOfFire);
	float getRateOfFire();


};

