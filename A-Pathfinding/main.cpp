#include <SFML/Graphics.hpp>
#include "pathfinding.h"
#include <iostream>
#include "delay.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	Pathfinding* pathfinding = new Pathfinding(40, 30);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			pathfinding->changeTile(pos / tileSize, Tile::WALL);

		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			pathfinding->changeTile(pos / tileSize, Tile::EMPTY);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			pathfinding->setEndPos(pos / tileSize);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{

			pathfinding->findPath();
			sf::Clock clock;
			sf::Time time = sf::seconds(0);
			while (time < sf::seconds(0.5f))
			{
				time = clock.getElapsedTime();
			}
		}
		
		window.clear();
		pathfinding->draw(&window);
		window.display();
	}

	return 0;
}