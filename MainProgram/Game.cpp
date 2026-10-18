#include "Game.h"
#include <iostream>
#include "State.h"


void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{

		//std::cout << window.pollEvent(event) << std::endl;
		
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameTime == playerPtr->getRateOfFire())
			{
				shooting();
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameTime == playerPtr->getRateOfFire())
			{
				shooting();

			}
		}
	}
}

State Game::update()
{

	elapsedTimeSinceLastUpdate += clock.restart();

	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;

		runDelay();
		motherShipSpawnTimer();

		playerPtr->move(0, WIDTH);
		moveMotherShip();

		moveShoot();
		movePowerUp();
		powerUpCollition();
		moveAllEnemyPtr();
		moveEnemyAllDown();
		checkIfEnemyReachBottom();
		collitionAllEnemys();
		collitionMotherShip();

		gameOver();

	}

	State state = State::NO_CHANGE;


	if (gameOverVar == true)
	{
		state = State::HIGHSCORE_INPUT;
	}

	return state;
}

void Game::render()
{
	window.clear();
	window.draw(*this->playerPtr);


	drawAllEnemyPtr();
	drawMotherShip();
	drawLives();
	drawAllShoots();
	drawAllTypesOfPickUp();
	window.draw(text);

	window.display();
}

Game::Game(Score * scorePtr)
	:GameState("Space Invaders")
{
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	gameScorePtr = scorePtr;

	scoreText();
	this->playerPtr = new Player(WIDTH / 2, HEIGHT - 80);
	this->motherShipPtr = new Mothership(-1000, -1000);

	spawnPowerUp();
	spawnAllShoots();
	placeAllEnemys();
	placeAllLives();

}

Game::~Game()
{
	delete this->playerPtr;
	delete this->motherShipPtr;
	delete this->hpPowerUpPtr;
	delete this->damagePowerUpPtr;
	delete this->rateOfFirePowerUpPtr;

	for (int i = 0; i < numberOfShoots; i++)
	{
		delete this->ArrayOfShootsPtr[i];
	}

	for (int i = 0; i < 3; i++)
	{
		delete this->playerLivePtr[i];
	}

	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			delete this->ArrayOfEnemyPtr[a1][a2];

		}
	}

	delete[] this->playerLivePtr;
	delete[] this->ArrayOfShootsPtr;
}




void Game::scoreText()
{
	font.loadFromFile("C:/windows/fonts/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Green);
	text.setPosition(20, 5);
	text.setString("Score: " + std::to_string(gameScorePtr->getScore()));
}

bool Game::enemyWin()
{
	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
		}

	}
	return 0;
}
int Game::randomFuntion()
{
	random = rand() % 3 + 0;

	return random;
}

//------------------------Shoot-------------------------------
void Game::moveShoot()
{
	for (int i = 0; i < numberOfShoots; i++)
	{
		if (ArrayOfShootsPtr[i]->getDeadOrOfSceen() == false)
		{
			if (ArrayOfShootsPtr[i]->getShootPositionY() > -100 && ArrayOfShootsPtr[i]->getShootPositionY() != -100 && ArrayOfShootsPtr[i]->getDeadOrOfSceen() == false)
			{
				ArrayOfShootsPtr[i]->moveShoot();
			}
			else if (ArrayOfShootsPtr[i]->getShootPositionY() >= -100)
			{
				spaceButtonIsPressed = false;
				deadShoot(i);

			}
		}
	}
}

void Game::deadShoot(int shootNumber)
{
	ArrayOfShootsPtr[shootNumber]->setShootPosition(-500, -500);
	ArrayOfShootsPtr[shootNumber]->setDeadOrOfSceen(true);
}

void Game::spawnAllShoots()
{
	for (int i = 0; i < numberOfShoots; i++)
	{
		this->ArrayOfShootsPtr[i] = new Shoots(-500, -500);
	}
}

void Game::drawAllShoots()
{
	for (int i = 0; i < numberOfShoots; i++)
	{
		if (ArrayOfShootsPtr[i]->getDeadOrOfSceen() == false)
		{
			window.draw(*ArrayOfShootsPtr[i]);
		}
	}
}

void Game::shooting()
{
	int shoot = shootNumber;
	spaceButtonIsPressed = true;

	this->ArrayOfShootsPtr[shoot]->setDeadOrOfSceen(false);
	this->ArrayOfShootsPtr[shoot]->spawnShoot(playerPtr->getPositionX() + 40, playerPtr->getPositionY());
	shootNumber++;
	if (shoot >= numberOfShoots-1)
	{
		shootNumber = 0;
	}

	delayTimer = true;
	spaceButtonDelayClock.restart();
}

//---------------------------------ShootEffect--------------------------

void Game::addDamage()
{
	playerPtr->setDamage(playerPtr->getDamage() + damagePowerUpPtr->getDamage());
}

void Game::addHp()
{
	if (playerPtr->getHp() < 3)
	{
		playerPtr->setHp(playerPtr->getHp() + hpPowerUpPtr->getHp());
	}
}

void Game::addRateOfFire()
{

	if (playerPtr->getRateOfFire() >= 0.2)
	{
		playerPtr->setRateOfFire(playerPtr->getRateOfFire() - rateOfFirePowerUpPtr->getRateOfFire());

	}

}

//-----------------------Enemy-------------------------------
void Game::placeAllEnemys()
{
	const float xPosEnemySpawnValue = 60;
	float xPosEnemySpawnFinalPos = 0;

	const float yPosEnemySpawnValue = 55;
	float yPosEnemySpawnFinalPos = 0;


	for (int a1 = 1; a1 <= numberOfRows; a1++)
	{
		yPosEnemySpawnFinalPos = yPosEnemySpawnValue * a1;
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			xPosEnemySpawnFinalPos = xPosEnemySpawnValue * a2;
			this->ArrayOfEnemyPtr[a1 - 1][a2] = new Enemy(xPosEnemySpawnFinalPos, yPosEnemySpawnFinalPos);
		}

	}
}

void Game::drawAllEnemyPtr()
{
	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			if (ArrayOfEnemyPtr[a1][a2]->getAlive() == true)
			{
				window.draw(*this->ArrayOfEnemyPtr[a1][a2]);
			}
		}
	}
}

void Game::moveAllEnemyPtr()
{
	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			this->ArrayOfEnemyPtr[a1][a2]->move(0, WIDTH);
		}
	}
}

void Game::moveEnemyAllDown()
{
	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			this->ArrayOfEnemyPtr[a1][a2]->moveDown(0, WIDTH);
			if (a1 == numberOfRows - 1 && a2 == numberOfEnemys - 1)
			{
				this->ArrayOfEnemyPtr[a1][a2]->setMoveDownCheck(false);

			}
		}
	}
}

bool Game::collitionAllEnemys()
{
	bool didCollide = false;

	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			if (this->ArrayOfEnemyPtr[a1][a2]->getAlive() == true)
			{
				for (int i = 0; i < numberOfShoots; i++)
				{
					if (this->ArrayOfEnemyPtr[a1][a2]->hit(*this->ArrayOfShootsPtr[i]))
					{
						didCollide = true;
						this->ArrayOfEnemyPtr[a1][a2]->setAlive(false);
						this->ArrayOfEnemyPtr[a1][a2]->isDead(-1000, -1000);
						gameScorePtr->setScore( gameScorePtr->getScore() + 100);
						text.setString("Score: " + std::to_string(gameScorePtr->getScore()));
						deadShoot(i);
						deadEnemy++;
					}
					else
					{
						didCollide = false;
					}
				}
			}
		}
	}
	return didCollide;
}

//-----------------------MotherShip-------------------------------
bool Game::collitionMotherShip()
{
	bool didCollide = false;

	if (this->motherShipPtr->getAlive() == true)
	{
		for (int i = 0; i < numberOfShoots; i++)
		{
			if (this->motherShipPtr->hit(*this->ArrayOfShootsPtr[i]))
			{
				didCollide = true;
				motherShipPtr->setHp(motherShipPtr->getHp() - playerPtr->getDamage());
				deadShoot(i);

				if (motherShipPtr->getHp() <= 0)
				{
					dropPowerUp(randomFuntion());
					gameScorePtr->setScore(gameScorePtr->getScore() + 1000);
					text.setString("Score: " + std::to_string(gameScorePtr->getScore()));
					this->motherShipPtr->setAlive(false);
					this->motherShipPtr->isDead(-1000, -1500);

				}

			}
			else
			{
				didCollide = false;
			}
		}
	}

	return didCollide;
}

void Game::spawnMotherShip()
{
	if (this->motherShipPtr->getAlive() == true)
	{
		this->motherShipPtr->setHp(2);
		this->motherShipPtr->setPosition(WIDTH, 50);
	}
}

void Game::drawMotherShip()
{
	if (motherShipPtr->getAlive() == true)
	{
		window.draw(*this->motherShipPtr);
	}
}

void Game::moveMotherShip()
{
	if (motherShipPtr->getAlive() == true)
	{
		motherShipPtr->move(0, WIDTH);
	}

}

//-----------------------Player-------------------------------

void Game::takeDamage()
{
	if (this->playerPtr->getHp() > 0)
	{
		this->playerPtr->setHp(playerPtr->getHp() - 1);

	}
}

//-----------------------PlayerLives-------------------------------
void Game::placeAllLives()
{
	const float xPosLiveSpawnValue = 85;
	float xPosLiveSpawnFinalPos = 0;

	for (int i = 1; i <= this->playerPtr->getHp(); i++)
	{
		xPosLiveSpawnFinalPos = WIDTH - (xPosLiveSpawnValue * i);
		this->playerLivePtr[i - 1] = new PlayerLives(sf::Color::Green, xPosLiveSpawnFinalPos, 0);
	}
}

void Game::drawLives()
{
	for (int i = 0; i < this->playerPtr->getHp(); i++)
	{
		window.draw(*this->playerLivePtr[i]);
	}
}

//------------------------Power Up-----------------------------
void Game::powerUpCollition()
{
	if (randomFuntion() == 0)
	{
		hpPowerUpCollition();
	}
	else if (randomFuntion() == 1)
	{
		damagePowerUpCollition();
	}
	else if (randomFuntion() == 2)
	{
		rateOfFirePowerUpCollition();
	}
}

bool Game::hpPowerUpCollition()
{
	bool didHitPickUp = false;

	if (this->hpPowerUpPtr->getPowerUpIsAlive() == true)
	{
		for (int i = 0; i < numberOfShoots; i++)
		{
			if (this->hpPowerUpPtr->hit(*this->ArrayOfShootsPtr[i]) == true)
			{
				didHitPickUp = true;
				deadShoot(i);
				this->hpPowerUpPtr->setPowerUpIsAlive(false);
				hpPowerUpPtr->powerUpIsDead();
				addHp();

			}
		}
	}

	return didHitPickUp;
}

bool Game::damagePowerUpCollition()
{
	bool didHitPickUp = false;

	if (this->damagePowerUpPtr->getPowerUpIsAlive() == true)
	{
		for (int i = 0; i < numberOfShoots; i++)
		{
			if (this->damagePowerUpPtr->hit(*this->ArrayOfShootsPtr[i]) == true)
			{
				didHitPickUp = true;
				deadShoot(i);
				this->damagePowerUpPtr->setPowerUpIsAlive(false);
				damagePowerUpPtr->powerUpIsDead();
				addDamage();

			}
		}
	}

	return didHitPickUp;
}

bool Game::rateOfFirePowerUpCollition()
{
	bool didHitPickUp = false;

	if (this->rateOfFirePowerUpPtr->getPowerUpIsAlive() == true)
	{
		for (int i = 0; i < numberOfShoots; i++)
		{
			if (this->rateOfFirePowerUpPtr->hit(*this->ArrayOfShootsPtr[i]) == true)
			{
				didHitPickUp = true;
				deadShoot(i);
				this->rateOfFirePowerUpPtr->setPowerUpIsAlive(false);
				rateOfFirePowerUpPtr->powerUpIsDead();
				addRateOfFire();

			}
		}
	}

	return didHitPickUp;
}

void Game::movePowerUp()
{
	if (hpPowerUpPtr->getPowerUpIsAlive() == true)
	{
		hpPowerUpPtr->fallDown();
		if (hpPowerUpPtr->getPositionY() >= HEIGHT)
		{
			hpPowerUpPtr->setPowerUpIsAlive(false);
		}
	}

	if (damagePowerUpPtr->getPowerUpIsAlive() == true)
	{
		damagePowerUpPtr->fallDown();
		if (damagePowerUpPtr->getPositionY() >= HEIGHT)
		{
			damagePowerUpPtr->setPowerUpIsAlive(false);
		}
	}

	if (rateOfFirePowerUpPtr->getPowerUpIsAlive() == true)
	{
		rateOfFirePowerUpPtr->fallDown();
		if (rateOfFirePowerUpPtr->getPositionY() >= HEIGHT)
		{
			rateOfFirePowerUpPtr->setPowerUpIsAlive(false);
		}
	}
}

void Game::dropPowerUp(int random)
{
	if (random == 0)
	{
		hpPowerUpPtr->setPowerUpIsAlive(true);
		hpPowerUpPtr->setPosition(motherShipPtr->getPositionX(), motherShipPtr->getPositionY());
	}
	else if (random == 1)
	{
		damagePowerUpPtr->setPowerUpIsAlive(true);
		damagePowerUpPtr->setPosition(motherShipPtr->getPositionX(), motherShipPtr->getPositionY());
	}
	else if (random == 2)
	{
		rateOfFirePowerUpPtr->setPowerUpIsAlive(true);
		rateOfFirePowerUpPtr->setPosition(motherShipPtr->getPositionX(), motherShipPtr->getPositionY());
	}
}

void Game::spawnPowerUp()
{
	this->hpPowerUpPtr = new HpPickUp(-2000.0f, -2000.0f);

	this->damagePowerUpPtr = new DamagePickUp(-2000.0f, -2000.0f);

	this->rateOfFirePowerUpPtr = new RateOfFirePickUp(-2000.0f, -2000.0f);
}

void Game::drawAllTypesOfPickUp()
{
	if (hpPowerUpPtr->getPowerUpIsAlive() == true)
	{
		window.draw(*this->hpPowerUpPtr);
	}

	if (damagePowerUpPtr->getPowerUpIsAlive() == true)
	{
		window.draw(*this->damagePowerUpPtr);
	}
	if (rateOfFirePowerUpPtr->getPowerUpIsAlive() == true)
	{
		window.draw(*this->rateOfFirePowerUpPtr);
	}
}

//-----------------------Delay--------------------------------
void Game::runDelay()
{
	if (delayTimer == true)
	{
		spaceButtonDelay -= spaceButtonDelayClock.getElapsedTime();
		gameTime = (float)spaceButtonDelay.asSeconds() + playerPtr->getRateOfFire();

		spaceButtonDelayClock.restart();

		if (gameTime == 0 || gameTime < 0)
		{
			delayTimer = false;
		}
	}
	else if (delayTimer == false)
	{
		spaceButtonDelayClock.restart();
		gameTime = playerPtr->getRateOfFire();
		spaceButtonDelay = sf::Time::Zero;
	}
}

void Game::motherShipSpawnTimer()
{
	if (motherShipPtr->getAlive() == false)
	{
		motherShipSpawn -= motherShipClock.getElapsedTime();
		spawnTimer = (float)motherShipSpawn.asSeconds() + spawnTimerValue;
		motherShipClock.restart();

		if (spawnTimer == 0 || spawnTimer < 0)
		{
			motherShipPtr->setAlive(true);
			spawnMotherShip();

			motherShipClock.restart();
			motherShipSpawn = sf::Time::Zero;

		}
	}
	else if (motherShipPtr->getAlive() == true)
	{
		motherShipClock.restart();
		motherShipSpawn = sf::Time::Zero;
	}
}

//-----------------------Win--------------------------------
void Game::gameOver()
{
	if (deadEnemy == totalNumerOfEnemys || playerPtr->getHp() == 0 || checkIfEnemyReachBottom() == true)
	{
		gameOverVar = true;
	}
}

bool Game::checkIfEnemyReachBottom()
{
	bool endGame = false;

	for (int a1 = 0; a1 < numberOfRows; a1++)
	{
		for (int a2 = 0; a2 < numberOfEnemys; a2++)
		{
			if (ArrayOfEnemyPtr[a1][a2]->getPositionY() >= HEIGHT - 80)
			{
				endGame = true;
				playerPtr->setHp(0);
			}
		}
	}

	return endGame;
}

bool Game::isWindowOpen()
{
	return window.isOpen();
}
