#pragma once
#include "Character.h"
#include "Shoots.h"
#include "PowerUp.h"
#include <SFML/Graphics.hpp>

class Mothership :public Enemy
{
private:

	static const int LEFT = -1;
	static const int Right = 1;
	static const int NO_DIERCTION = 0;
	int direction = LEFT;

public:

	Mothership(float xPos, float yPos,float speed = 3, std::string textureString = "../../Resource File/images/Enemy_MotherShip.png");

	Mothership();

	~Mothership();

	void move(float leftBounds, float rightBounds);

};
