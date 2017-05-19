#include "pathfinding.h"


Pathfinding::Pathfinding(int x, int y)
{
	map.resize(x);
	for (int i = 0; i< x; i++)
	{
		map[i].resize(y);
	}

	for (int xx = 0; xx < x; xx++)
	{
		for (int yy = 0; yy < y; yy++)
			map[xx][yy] = Tile::EMPTY;
	}
}

void Pathfinding::draw(sf::RenderWindow * window)
{
	sf::RectangleShape rect;
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(tileSize - 1, tileSize - 1));
	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[x].size(); y++)
		{

			rect.setPosition(x*tileSize, y*tileSize);
			if (map[x][y] == Tile::EMPTY)
				rect.setFillColor(sf::Color::White);
			else rect.setFillColor(sf::Color::Black);
			window->draw(rect);
		}
	}

	for (auto it = path.begin(); it != path.end(); it++)
	{
		rect.setPosition(it->x*tileSize, it->y*tileSize);
		rect.setFillColor(sf::Color::Red);
		window->draw(rect);
	}

	rect.setPosition(startPos.x*tileSize,startPos.y*tileSize);
	rect.setFillColor(sf::Color::Blue);
	window->draw(rect);

	rect.setPosition(endPos.x*tileSize, endPos.y*tileSize);
	rect.setFillColor(sf::Color::Magenta);
	window->draw(rect);

}

void Pathfinding::setEndPos(sf::Vector2i pos)
{
	endPos = pos;
}

void Pathfinding::changeTile(sf::Vector2i pos, Tile tile)
{
	map[pos.x][pos.y] = tile;
}
Cost Pathfinding::getCost(sf::Vector2i tile, float costG)
{
	Cost cost;
	cost.g = costG + 1;
	cost.h = abs(tile.x - endPos.x) + abs(tile.y - endPos.y);
	cost.total = cost.g + cost.h;
	return cost;
}
bool Pathfinding::isWall(sf::Vector2i pos)
{
	if (pos.x >= 0 && pos.x < map.size() && pos.y >= 0 && pos.y < map[0].size())
	{
		if (map[pos.x][pos.y] == Tile::WALL)
			return true;
		return false;
	}
	return true;
}
void Pathfinding::findPath()
{
	openList.clear();
	closedList.clear();
	path.clear();
	int pathSteps = 0;
	const int MAX_LOWEST_COST = 4000;
	pNode start{ startPos,startPos,0 };
	openList.push_front(start);
	do
	{
		int lowestCost = MAX_LOWEST_COST;
		std::list<pNode>::iterator currentNode;
		for (auto it = openList.begin(); it != openList.end(); it++)
		{
			//seeking the node with lowest cost
			if (it->cost.total < lowestCost)
			{
				currentNode = it;
				lowestCost = it->cost.total;
			}
		}
		closedList.push_front(*currentNode);
		openList.erase(currentNode);

		if (closedList.front() == endPos)
		{
			//path found
			currentNode = closedList.begin();
			while (currentNode->point != startPos)
			{
				path.push_back(currentNode->point);
				auto it = std::find(closedList.begin(), closedList.end(), currentNode->parentPoint);
				if (it != closedList.end())
					currentNode = it;
			}

			break;
		}

		std::list<pNode> temp;
		sf::Vector2i tile = closedList.front().point;
		pNode leftNode{ sf::Vector2i(tile.x - 1, tile.y),tile, 0 };
		pNode rightNode{ sf::Vector2i(tile.x + 1, tile.y),tile, 0 };
		pNode topNode{ sf::Vector2i(tile.x, tile.y - 1),tile, 0 };
		pNode bottomNode{ sf::Vector2i(tile.x, tile.y + 1),tile, 0 };
		temp.push_back(leftNode);
		temp.push_back(topNode);
		temp.push_back(rightNode);
		temp.push_back(bottomNode);
		int WALL = 2;
		for (auto it = temp.begin(); it != temp.end(); it++)
		{
			if (!isWall(it->point) && std::find(closedList.begin(), closedList.end(), *it) == closedList.end())
			{
				auto itt = std::find(openList.begin(), openList.end(), *it);
				if (itt != openList.end())
					itt->cost = getCost(it->point, closedList.front().cost.g);
				else
				{
					it->cost = getCost(it->point, closedList.front().cost.g);
					openList.push_front(*it);
				}

			}
		}
		temp.clear();
		pathSteps++;
		std::cout << "Step : " << pathSteps - 1 << std::endl;
	} while (!openList.empty() && pathSteps < 6000);
}
