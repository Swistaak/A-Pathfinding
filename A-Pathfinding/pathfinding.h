#include <cmath>
#include <list>
#include <vector>
#include <SFML\Graphics.hpp>
#include "tile.h"
#include <iostream>
struct Cost
{
	int total;
	int g;
	int h;
};
struct pNode
{
	sf::Vector2i point;
	sf::Vector2i parentPoint;
	Cost cost;
	bool operator==(const pNode &p) const { return point == p.point; }
	bool operator==(const sf::Vector2i &parent) const { return point == parent; }
};
class Pathfinding
{
public:
	Pathfinding(int x, int y);
	void findPath();
	void draw(sf::RenderWindow *window);
	void setEndPos(sf::Vector2i pos);
	void changeTile(sf::Vector2i pos, Tile tile);
	void drawOpenList(sf::RenderWindow *window);
	void drawClosedList(sf::RenderWindow *window);
	void wipe();
private:
	Cost getCost(sf::Vector2i tile, float costG);
	std::list<pNode> openList;
	std::list<pNode> closedList;
	std::list<sf::Vector2i> path;
	std::vector<std::vector<Tile>> map;
	sf::Vector2i startPos = sf::Vector2i(1, 1);
	sf::Vector2i endPos;
	bool isWall(sf::Vector2i pos);
};