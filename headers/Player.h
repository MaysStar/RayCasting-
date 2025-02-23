#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#define M_PI 3.14159265358979323846
#define widthMapInSymbols 11
#define heightMapInSymbols 11

class Player{
    sf::Vector2f positionPlayerInCMap;
    sf::Vector2f positionPlayerInSFMLMap;

public:
    Player(char mapInSymbols[heightMapInSymbols][widthMapInSymbols]);
    void setCircleParameters(sf::CircleShape& circlePlayer, int i, int j);
    void movementPlayer(char mapInSymbols[heightMapInSymbols][widthMapInSymbols], float deltaTime, std::vector<sf::RectangleShape>& allCube);
    bool checkCollision(sf::Vector2f newPosition, std::vector<sf::RectangleShape>& allCube);
    sf::CircleShape circlePlayer;
    float playerAngle = -85.0f;
    const int FOV = 120;
};

