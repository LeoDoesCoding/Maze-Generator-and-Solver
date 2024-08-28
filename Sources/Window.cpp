#pragma once
#include <SFML/Graphics.hpp>
#include "../Headers/GUI.h"
#include <iostream> //For debugging

using namespace sf;
sf::RenderWindow GUI::window;
Maze GUI::maze;

int main() {
    GUI::setup();
    return 0;
};


void GUI::setup() {
    window.create(VideoMode(950, 800), "Maze Solver");
    window.setKeyRepeatEnabled(false);
    srand(time(NULL));
    maze.randomMaze();
    drawMaze();

    Solver::DFS(maze.getStart(), maze.getGoal());

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    std::cout << "Space pressed" << std::endl;
                    maze = Maze();
                }
            }
        }
    }
}

void GUI::drawPath(Node* first, Node* second) {
    second->nodeShape.setFillColor(sf::Color::Green);
    maze.getBridge({ static_cast<short>(first->nodeShape.getPosition().x/maze.getMult()), static_cast<short>(first->nodeShape.getPosition().y / maze.getMult()) }, { static_cast<short>(second->nodeShape.getPosition().x / maze.getMult()), static_cast<short>(second->nodeShape.getPosition().y / maze.getMult()) }).setFillColor(sf::Color::Green);
    drawMaze();
}

void GUI::drawMaze() {
    window.clear();
    RectangleShape walls(sf::Vector2f(maze.getX() * maze.getMult(), maze.getY() * maze.getMult()));
    walls.setPosition(maze.getMult(), maze.getMult());
    walls.setFillColor(Color::Blue);
    window.draw(walls);
    for (auto& space : maze.getMaze()) {
        window.draw(space.second->nodeShape);
    }
    for (auto& bridge : maze.getBridges()) {
        window.draw(bridge.second);
    }
    window.display();
}