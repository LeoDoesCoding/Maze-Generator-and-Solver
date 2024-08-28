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
    sf::RectangleShape & getBridge(Coordinates node1, Coordinates node2) {
        if (bridges.count({ node1, node2 }) == 0) {
            return bridges[std::make_pair(node2, node1)];
        } else { return bridges[std::make_pair(node1, node2)]; }
     }
    auto & getMaze() { return maze; }
    bool isComplete() & { return complete; }
    Node* getStart() & { return maze[{1, 1}]; }
    Node* getGoal() & { return maze[{dimensions.X, dimensions.Y}]; }

private:
    std::map<Coordinates, Node*> maze;  //Corrisponding maze coordinates
    Coordinates dimensions;             //Maze size
    std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> bridges;  //Connecting lines between nodes in maze visual
    void setDimensions(short x, short y);
    void placeNode(Coordinates, Coordinates, Directions);
    short mult;
    void gen1();
    void gen2();
    bool complete = false;
    Directions directions[4] = { NORTH, EAST, SOUTH, WEST };
};