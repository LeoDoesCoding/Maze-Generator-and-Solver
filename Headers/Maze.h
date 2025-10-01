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
    auto & getMaze() { return maze; }
    Node* getStart() & { return maze[{1, 1}]; }
    Node* getGoal() & { return maze[{dimensions.X, dimensions.Y}]; }
    void resetSolver();

private:
    std::map<Coordinates, Node*> maze;  //Corrisponding maze coordinates
    Coordinates dimensions;             //Maze size
    void setDimensions(short x, short y);
    void placeNode(Coordinates, Coordinates, Directions);
    void gen1();
};