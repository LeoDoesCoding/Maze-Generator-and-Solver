#pragma once
#include "Nodes.h"
#include "SFML/Graphics/Vertex.hpp"
#include <map>

class Maze {
public:
    //static void defaultMaze();
    static void randomMaze();
    static short getX() { return dimensions.X; }
    static short getY() { return dimensions.Y; }
    static auto & getBridges() { return bridges; }
    static auto & getMaze() { return maze; }

private:
    static std::map<Coordinates, Node*> maze;  //Corrisponding maze coordinates
    static Coordinates dimensions;             //Maze size
    static void setDimensions(short x, short y);
    static std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> bridges;  //Connecting lines between nodes in maze visual
    static enum Directions {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        DIRECTIONS
    };
};