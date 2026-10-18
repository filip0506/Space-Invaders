#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Mothership.h"
#include "Player.h"
#include "Shoots.h"
#include "PlayerLives.h"
#include "HpPickUp.h"
#include "DamagePickUp.h"
#include "RateOfFirePickUp.h"
#include "Score.h"

class Game : public GameState
{
public:
	static const int HEIGHT = 800;
	static const int WIDTH = 900;

	static const int numberOfEnemys = 11;
	static const int numberOfRows = 4;
	static const int numberOfShoots = 20;
	

private:

	int totalNumerOfEnemys = numberOfEnemys*numberOfRows;

	float gameTime = 5;
	float spawnTimer = 0;
	float spawnTimerValue = 15;

	int deadEnemy = 0;

	int hpDisplaySize = 3;
	float timeDelay = 0;

	int shootNumber = 0;
	bool spaceButtonIsPressed = false;
	Score *gameScorePtr;
	int random;

	bool delayTimer = false;
	bool spawnDelayTimer = false;
	bool gameOverVar = false;

	sf::Clock clock;
	sf::Clock spaceButtonDelayClock;
	sf::Clock motherShipClock;
	
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	sf::Time spaceButtonDelay = sf::Time::Zero;
	sf::Time motherShipSpawn = sf::Time::Zero;
	   
	sf::Text text;
	sf::Font font;

	Player *playerPtr;
	PlayerLives* *playerLivePtr = new PlayerLives*[hpDisplaySize];
	Shoots* *ArrayOfShootsPtr = new Shoots *[numberOfShoots];

	Enemy *ArrayOfEnemyPtr[numberOfRows][numberOfEnemys];

	Mothership *motherShipPtr;
	HpPickUp *hpPowerUpPtr;
	DamagePickUp *damagePowerUpPtr;
	RateOfFirePickUp *rateOfFirePowerUpPtr;

public:
	Game(Score *scorePtr);
	virtual ~Game();
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;

	virtual bool isWindowOpen() override;


	void scoreText();
	bool enemyWin();
	int randomFuntion();

	//Shoot function
	void moveShoot();
	void deadShoot(int shootNumber);
	void spawnAllShoots();
	void drawAllShoots();

	void shooting();

	//Shoot effect
	void addDamage();
	void addHp();
	void addRateOfFire();


	// Enemy function
	void placeAllEnemys();
	void drawAllEnemyPtr();
	void moveAllEnemyPtr();
	void moveEnemyAllDown();
	bool collitionAllEnemys();

	// Mother ship function
	bool collitionMotherShip();
	void spawnMotherShip();
	void drawMotherShip();
	void moveMotherShip();

	//Player
	void takeDamage();

	//PlayerLives
	void placeAllLives();
	void drawLives();

	// PowerUp
	void powerUpCollition();
	bool hpPowerUpCollition();
	bool damagePowerUpCollition();
	bool rateOfFirePowerUpCollition();

	void movePowerUp();
	void dropPowerUp(int random);
	void spawnPowerUp();
	void drawAllTypesOfPickUp();

	// Delay
	void runDelay();
	void motherShipSpawnTimer();

	// Win
	void gameOver();
	bool checkIfEnemyReachBottom();

};
