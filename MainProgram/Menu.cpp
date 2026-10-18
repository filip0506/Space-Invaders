#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::moveUp()
{
	if (this->selected > 0)
	{
		this->alternatives[this->selected].setFillColor(sf::Color::Yellow); // avmarkerar tidigare vald
		this->selected--; // uppdaterar vald
		this->alternatives[this->selected].setFillColor(sf::Color::Red); // makerar en vald
	}

}

void Menu::moveDown()
{
	if (this->selected < 1)
	{
		this->alternatives[this->selected].setFillColor(sf::Color::Yellow); // avmarkerar tidigare vald
		this->selected++; // uppdaterar vald
		this->alternatives[this->selected].setFillColor(sf::Color::Red); // makerar en vald
	}

}

Menu::Menu()
	:GameState("Menu")
{
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	alternatives[0].setFont(font);
	alternatives[0].setFillColor(sf::Color::Red);
	alternatives[0].setCharacterSize(30);
	alternatives[0].setString("Play");
	alternatives[0].setPosition(200.f, 200.f);

	alternatives[1].setFont(font);
	alternatives[1].setFillColor(sf::Color::Yellow);
	alternatives[1].setCharacterSize(30);
	alternatives[1].setString("Exit");
	alternatives[1].setPosition(200.f, 350.f);

	
	selected = 0;
	done = false;
}

Menu::~Menu()
{
}

State Menu::update()
{
	State state = State::NO_CHANGE;

	if (this->done == true)
	{
		switch (this->selected)
		{
			case 0:
				state = State::PLAY;
				break;
			case 1:
				state = State::EXIT;
				break;
		}

	}


	return state;
}

void Menu::render()
{
	window.clear();

	for (int i = 0; i < 2; i++)
	{
		window.draw(this->alternatives[i]);
	}
	
	window.display();
}

void Menu::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				this->moveUp();
				cout << "A" << endl;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				this->moveDown();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				this->done = true;
			}
		}
	}
}

bool Menu::isWindowOpen()
{
	return window.isOpen();
}

