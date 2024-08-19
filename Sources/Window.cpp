#include <SFML/Graphics.hpp>
#include "../Headers/Maze.h"
#include "../Headers/Solver.h"
#include <iostream> //For debugging

using namespace sf;

int main() {
    RenderWindow window(VideoMode(950, 800), "Maze Solver");
    Maze::randomMaze();
    //Generate visual for maze
    RectangleShape walls(sf::Vector2f(Maze::getX() * 100,  Maze::getY() * 100));
    walls.setPosition(100, 100);
    walls.setFillColor(Color::Blue);
    window.draw(walls);
    for (auto& space : Maze::getMaze()) {
        window.draw(space.second->nodeShape);
    }
    for (auto& bridge : Maze::getBridges()) {
        window.draw(bridge.second);
    }
    window.display();

    //PathNode* path = Solver::DFS(Maze::maze->start);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
};