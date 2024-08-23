#include <SFML/Graphics.hpp>
#include "../Headers/Maze.h"
#include "../Headers/Solver.h"
#include <iostream> //For debugging

using namespace sf;
void drawMaze(Maze*, RenderWindow*);

int main() {
    RenderWindow window(VideoMode(950, 800), "Maze Solver");
    window.setKeyRepeatEnabled(false);
    srand(time(NULL));
    Maze *maze = new Maze();
    maze->randomMaze();
    drawMaze(maze, &window);

    //PathNode* path = Solver::DFS(maze.maze->start);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    std::cout << "Space pressed" << std::endl;
                    delete maze;
                    maze = new Maze();
                    maze->randomMaze();
                    drawMaze(maze, &window);
                }
            }
        }
    }

    return 0;
};


void drawMaze(Maze* maze, RenderWindow* window) {
    //Generate visual for maze
    window->clear();
    RectangleShape walls(sf::Vector2f(maze->getX() * maze->getMult(), maze->getY() * maze->getMult()));
    walls.setPosition(maze->getMult(), maze->getMult());
    walls.setFillColor(Color::Blue);
    window->draw(walls);
    for (auto& space : maze->getMaze()) {
        window->draw(space.second->nodeShape);
    }
    for (auto& bridge : maze->getBridges()) {
        window->draw(bridge.second);
    }
    window->display();
};