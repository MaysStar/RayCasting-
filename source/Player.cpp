#include "Player.h"


Player::Player(char mapInSymbols[heightMapInSymbols][widthMapInSymbols]) {
    mapInSymbols[heightMapInSymbols / 2][widthMapInSymbols / 2] = '*';
    positionPlayerInCMap.y = heightMapInSymbols / 2;
    positionPlayerInCMap.x = widthMapInSymbols / 2;
    setCircleParameters(circlePlayer, heightMapInSymbols, widthMapInSymbols);
}

void Player::movementPlayer(char mapInSymbols[heightMapInSymbols][widthMapInSymbols], float deltaTime, std::vector<sf::RectangleShape>& allCube) {
    positionPlayerInSFMLMap = circlePlayer.getPosition();
    float speed = 30;
    sf::Vector2f newPosition = positionPlayerInSFMLMap;

    playerAngle += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? 2.0f : 0) -
        (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? 2.0f : 0);
    circlePlayer.setRotation(playerAngle);
    //std::cout << circlePlayer.getRotation() << std::endl;



    float angleRad = playerAngle * M_PI / 180.0f;
    sf::Vector2f step(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        step.x += deltaTime * cos(angleRad) * speed;
        step.y += deltaTime * sin(angleRad) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        step.x -= deltaTime * cos(angleRad) * speed;
        step.y -= deltaTime * sin(angleRad) * speed;
    }

    sf::Vector2f tempX = newPosition + sf::Vector2f(step.x, 0);
    sf::Vector2f tempY = newPosition + sf::Vector2f(0, step.y);

    bool canMoveX = !checkCollision(tempX, allCube);
    bool canMoveY = !checkCollision(tempY, allCube);

    if (canMoveX) {
        newPosition.x = tempX.x;
    }
    if (canMoveY) {
        newPosition.y = tempY.y;
    }

    circlePlayer.setPosition(newPosition);
    positionPlayerInCMap.x = newPosition.x / (circlePlayer.getRadius() * 2);
    positionPlayerInCMap.y = newPosition.y / (circlePlayer.getRadius() * 2);
}

void Player::setCircleParameters(sf::CircleShape& circlePlayer, int i, int j) {
    circlePlayer.setRadius(3.0f);
    circlePlayer.setOrigin(circlePlayer.getRadius(), circlePlayer.getRadius());
    circlePlayer.setFillColor(sf::Color(127, 67, 127));
    circlePlayer.setPosition(sf::Vector2f((10 * j), (10 * i)));
}

bool Player::checkCollision(sf::Vector2f newPosition, std::vector<sf::RectangleShape>& allCube) {
    sf::CircleShape tempCircle = circlePlayer;
    tempCircle.setPosition(newPosition);

    for (auto& cube : allCube) {
        if (tempCircle.getGlobalBounds().intersects(cube.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}