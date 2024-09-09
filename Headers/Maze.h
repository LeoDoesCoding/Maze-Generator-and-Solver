#pragma once
#include "Nodes.h"
#include "SFML/Graphics/Vertex.hpp"
#include <iostream>
#include <map>
#include <random>

class Maze {
public:
    void randomMaze(short size);
    short getX() { return dimensions.X; }
    short getY() { return dimensions.Y; }
    short getMult() { return mult; }
    auto & getBridges() { return bridges; }
    sf::RectangleShape & getBridge(Coordinates node1, Coordinates node2) { return bridges[std::make_pair(node2, node1)]; }
    auto & getMaze() { return maze; }
    Node* getStart() & { return maze[{1, 1}]; }
    Node* getGoal() & { return maze[{dimensions.X, dimensions.Y}]; }

private:
    std::map<Coordinates, Node*> maze;  //Corrisponding maze coordinates
    Coordinates dimensions;             //Maze size
    std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> bridges;  //Connecting lines between nodes in maze visual
    short mult;
    void setDimensions(short x, short y);
    void placeNode(Coordinates, Coordinates, Directions);
    void gen1();
    /*Gen2 setup preparation
    void gen2();
    bool complete = false;
    Directions directions[4] = { NORTH, EAST, SOUTH, WEST };*/
};