#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Enemy.h"
class Player: public Character
{
private:

	int damage = 1;
	float rateOfFire = 0.5f;

	   
public:
	Player(float xPos, float yPos, float speed = 6, std::string textureString = "../../Resource File/images/SpaceInvaders_Player.png");
	Player();
	~Player();

	void move(float leftBounds, float rightBounds);
	bool hit(Enemy & theEnemy) const;

	void setRateOfFire(float rateOfFire);
	float getRateOfFire();

	void setDamage(int damage);
	int getDamage();

};

