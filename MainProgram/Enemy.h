#pragma once
#include "Character.h"
#include "Shoots.h"
#include <SFML/Graphics.hpp>

class Enemy:public Character
{
private:
	
	static const int LEFT = -1;
	static const int Right = 1;
	static const int NO_DIERCTION = 0;

	static int direction;
	static bool globalMoveDownVar;

public:

	Enemy(float xPos, float yPos, float speed = 1.2f, std::string textureString = "../../Resource File/images/enemy.png");
	Enemy();
	~Enemy();
	
	void move(float leftBounds, float rightBounds);
	void moveDown(float leftBounds,float rightBounds);

	void setDirection(int direction);
	int getDirection();

	void setMoveDownCheck(bool globalMoveDownVar);
	bool getmoveDownCheck();

	bool hit(Shoots & theShoot) const;

};
