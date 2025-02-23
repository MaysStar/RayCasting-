#include "Ray.h"


Ray::Ray(sf::Vector2f cordForPosition, std::vector<sf::RectangleShape>& allCube, int startAngle, int endAngle) {
	position = cordForPosition;
	for (float i = startAngle; i <= endAngle; i++) {
	    sf::Vector2f direct;
	    radians = i * M_PI / 180;
	    direction = { cos(radians), sin(radians) };
	    end = castRay(position, direction, allCube);

	    sf::VertexArray ray(sf::Lines, 2);
	    ray[0].position = position;
	    ray[0].color = sf::Color::Red;
	    ray[1].position = end;
	    ray[1].color = sf::Color::Red;

	    ends.push_back(end);
	    allLines.push_back(ray);
	    direct = end - position;
	    float distance = sqrt(direct.x * direct.x + direct.y * direct.y);
	    distances.push_back(distance);
	    rayAngles.push_back(i);
	}
}

sf::Vector2f Ray::castRay(sf::Vector2f start, sf::Vector2f direction, std::vector<sf::RectangleShape>& allCube) {
	float stepSize = 1;
	sf::Vector2f currentPos = start;
	
	for (unsigned short i = 0; i < 400.f; i += stepSize) {
	    currentPos += direction * stepSize;
	
	    for (auto& cube : allCube) {
	        sf::FloatRect bounds = cube.getGlobalBounds();
	
	        if (bounds.contains(currentPos)) {
	            return currentPos; 
	        }
	    }
	}
	return currentPos; 
}
