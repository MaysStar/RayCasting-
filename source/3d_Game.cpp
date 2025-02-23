#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window.hpp>
#include "Ray.h"
#include "Player.h"
#include "Map.h"
#define M_PI 3.14159265358979323846
#define widthMapInSymbols 11
#define heightMapInSymbols 11

int main() {
    float h = 1000;
    float h2;
    float d;
    float d2 = 1;
    float b = 300;
    float b2;
    int windowWidth = 1800;
    int windowHeight = 1000;
    sf::String title = "3D RayСasting";
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Default, sf::ContextSettings(24));
    window.setActive(true);
    char mapNumberOne[heightMapInSymbols][widthMapInSymbols]{
        {'#','#','#','#','#','#','#','#','#','#','#'},
        {'#',' ',' ',' ',' ','#',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ','#','#',' ',' ',' ',' ','#'},
        {'#','#',' ',' ',' ','#','#',' ',' ',' ','#'},
        {'#','#','#',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ','#',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#','#','#',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#',' ','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#','#'}
    };

    Map myMap(mapNumberOne);
    Player myPlayer(mapNumberOne);
    Ray myRay(myPlayer.circlePlayer.getPosition(), myMap.allCube, myPlayer.playerAngle - myPlayer.FOV / 2, myPlayer.playerAngle + myPlayer.FOV / 2);
    window.clear();
    
    
    //window.clear();
    sf::Clock clock;
    sf::VertexArray line(sf::Lines, 2);

    line[0].color = sf::Color::White;
    line[0].position = sf::Vector2f(0, h / 2);
    line[1].color = sf::Color::White;
    line[1].position = sf::Vector2f(1800, h / 2);

    float projectionPlaneDist = (windowWidth / 2.f) / std::tan((myPlayer.FOV * M_PI / 180.f) / 2.f);
    float cubeSize = 40.f;
    float normalizeLines = 10;

    while (window.isOpen()) {
        window.clear();
        sf::Time deltaTime = clock.getElapsedTime();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2f movement(0.f, 0.f);

        myRay = Ray(myPlayer.circlePlayer.getPosition(), myMap.allCube, myPlayer.playerAngle - myPlayer.FOV / 2, myPlayer.playerAngle + myPlayer.FOV / 2);
        float startAngle = myPlayer.playerAngle - myPlayer.FOV / 2.f;
        float endAngle = myPlayer.playerAngle + myPlayer.FOV / 2.f;

        myPlayer.movementPlayer(mapNumberOne, deltaTime.asSeconds(), myMap.allCube);

        float lineHeight2;
        int numRays = (int)myRay.distances.size();
        float columnWidth = (float)windowWidth / (float)numRays;

        for (int i = 0; i < numRays; i++)
        {

            float angleDeltaRad = (myRay.rayAngles[i] - myPlayer.playerAngle) * M_PI / 180.f;
            float correctedDist = myRay.distances[i] * cos(angleDeltaRad);


            float lineHeight = (projectionPlaneDist * 10.0f ) / correctedDist;

            if (i > 1) {
                float difference;
                difference = lineHeight2 - lineHeight;
                std::cout << difference << std::endl;
            }
            float columnX = i * columnWidth;

            float topY = (windowHeight / 2.f) - (lineHeight / 2.f);
            sf::RectangleShape wall(sf::Vector2f(columnWidth, lineHeight));
            wall.setPosition(columnX, topY);
            float shade = 255 - (correctedDist * 2.f);
            if (shade < 20) shade = 20;
            sf::Color colorWall(0, shade, 0);
            wall.setFillColor(colorWall);

            // (ДОДАТКОВО) Якщо хочете натягнути текстуру:
            // wall.setTexture(&someWallTexture);
            // wall.setTextureRect(sf::IntRect(...)); // потрібна логіка визначення "колонки" текстури

            // 6) Малюємо стіну
            window.draw(wall);
            lineHeight2 = lineHeight;
        }

        for (auto& cube : myMap.allCube) window.draw(cube);

        for (auto& space : myMap.allSpace) window.draw(space);

        window.draw(myPlayer.circlePlayer);

        for (auto& ray : myRay.allLines) window.draw(ray);

        window.display();
        
    }

    return 0;

}