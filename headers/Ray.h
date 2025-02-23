#pragma once 
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Ray{
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::Vector2f end;
    float radians;
public:
    Ray(sf::Vector2f cordForPosition, std::vector<sf::RectangleShape>& allCube, int startAngle, int endAngle);
    sf::Vector2f castRay(sf::Vector2f start, sf::Vector2f direction, std::vector<sf::RectangleShape>& allCube);

    std::vector< sf::VertexArray> allLines;
    std::vector<float> distances;
    std::vector<float> rayAngles;
    std::vector<sf::Vector2f> ends;
};

