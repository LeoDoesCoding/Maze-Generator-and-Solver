#pragma once
#include "Nodes.h"
#include "SFML/Graphics/Vertex.hpp"
#include <map>

class Maze {
public:
    void randomMaze();
    short getX() { return dimensions.X; }
    short getY() { return dimensions.Y; }
    short getMult() { return mult; }
    auto & getBridges() { return bridges; }
    auto & getMaze() { return maze; }

private:
    std::map<Coordinates, Node*> maze;  //Corrisponding maze coordinates
    Coordinates dimensions;             //Maze size
    std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> bridges;  //Connecting lines between nodes in maze visual
    void setDimensions(short x, short y);
    void placeNode(Coordinates, Coordinates, Directions);
    short mult;
    void gen1();
    void gen2();
    Directions directions[4] = { NORTH, EAST, SOUTH, WEST };
};