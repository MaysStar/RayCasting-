#pragma once
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#define widthMapInSymbols 11
#define heightMapInSymbols 11

class Map{
public:
	std::vector<sf::RectangleShape> allCube;
	std::vector<sf::RectangleShape> allSpace;
	Map(char mapInSymbols[heightMapInSymbols][widthMapInSymbols]);
	void setCubeParameters(sf::RectangleShape& cube, int i, int j, int widthCube);
	void setSpaceParameters(sf::RectangleShape& cube, int i, int j, int widthSpace);
};

