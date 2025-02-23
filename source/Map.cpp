#include "Map.h"


Map::Map(char mapInSymbols[heightMapInSymbols][widthMapInSymbols]) {
    int widthCube = 20;
    for (int i = 0; i < heightMapInSymbols; i++) {
        for (int j = 0; j < widthMapInSymbols; j++) {
            if (mapInSymbols[i][j] == '#') {
                sf::RectangleShape cube;
                setCubeParameters(cube, i, j, widthCube);
                allCube.push_back(cube);
            }
            else if (mapInSymbols[i][j] == ' ') {
                sf::RectangleShape space;
                setSpaceParameters(space, i, j, widthCube);
                allSpace.push_back(space);
            }
        }
    }
}

void Map::setCubeParameters(sf::RectangleShape& cube, int i, int j, int widthCube) {
    cube.setSize(sf::Vector2f(widthCube, widthCube));
    cube.setOrigin(sf::Vector2f(widthCube / 2, widthCube / 2));
    cube.setFillColor(sf::Color(67, 67, 67));
    cube.setOutlineThickness(3.0f);
    cube.setOutlineColor(sf::Color(128, 128, 128));
    cube.setPosition(sf::Vector2f(widthCube / 2 + j * (widthCube + cube.getOutlineThickness() * 2), widthCube / 2 + i * (widthCube + cube.getOutlineThickness() * 2)));
}

void Map::setSpaceParameters(sf::RectangleShape& cube, int i, int j, int widthSpace) {
    cube.setSize(sf::Vector2f(widthSpace, widthSpace));
    cube.setOrigin(sf::Vector2f(widthSpace / 2, widthSpace / 2));
    cube.setFillColor(sf::Color(0, 0, 67));
    cube.setOutlineThickness(3.0f);
    cube.setOutlineColor(sf::Color(0, 0, 67));
    cube.setPosition(sf::Vector2f(widthSpace / 2 + j * (widthSpace + cube.getOutlineThickness() * 2), widthSpace / 2 + i * (widthSpace + cube.getOutlineThickness() * 2)));
}