#include <SFML\Graphics.hpp>
void delay(float seconds)
{
	sf::Clock clock;
	sf::Time time = sf::seconds(0);
	while (time < sf::seconds(seconds))
	{
		time = clock.getElapsedTime();
	}
}