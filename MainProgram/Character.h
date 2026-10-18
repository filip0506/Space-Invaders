#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Character:public sf::Drawable
{
private:
	
	int hp;
	float speed;
	bool alive = true;

	sf::Texture texture;
	sf::Sprite sprite;


protected:

	void moveSprite(float xPos,float yPos);
	void setScale(float xScale, float yScale);
	void setColor(sf::Color color);


public:

	//kalla på construtor i inziierings lisatan
	Character(float xPos, float yPos,float speed, std::string textureString);

	Character();
	virtual ~Character();

	void setHp(int hp);
	int getHp();

	void setSpeed(float speed);
	float getSpeed();

	void setAlive(bool alive);
	bool getAlive();

	void isDead(float xPos,float yPos);

	void setPosition(float xPos,float yPos);
	float getPositionX();
	float getPositionY();





	virtual void move(float leftBounds, float rightBounds) = 0;

	sf::FloatRect getGlobalBounds() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

};

