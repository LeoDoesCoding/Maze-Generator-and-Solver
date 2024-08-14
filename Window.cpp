#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Solver.h"
#include <iostream>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(950, 800), "Maze Solver");
    //CircleShape shape(100.f);
    //shape.setFillColor(Color::Green);

    Maze::defaultMaze();
    //Generate visual for maze
    RectangleShape walls(sf::Vector2f(Maze::getX() * 100,  Maze::getY() * 100));
    walls.setFillColor(Color::Green);

    //PathNode* path = Solver::DFS(Maze::maze->start);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(walls);
        window.display();
    }

    return 0;
}