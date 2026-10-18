#pragma once
#include <SFML/Graphics.hpp>

class Shoots: public sf::Drawable
{

private:
	float shootTravelSpeed;
	sf::Texture texture;
	sf::Sprite sprite;
	bool isDeadOrOutOfScreen = false;
	
public:
	Shoots(float xPos,float yPos,float shootTravelSpeed = 10.0f);
	Shoots();
	~Shoots();

	void moveShoot();

	float getShootPositionX();
	float getShootPositionY();
	void setShootPosition(float xPos,float yPos);

	void spawnShoot(float xPos, float yPos);

	void setDeadOrOfSceen(bool deadOrOfSceen);
	bool getDeadOrOfSceen();

	sf::FloatRect getGlobalBounds() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

};

