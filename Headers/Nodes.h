#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
struct Node;
struct PathNode;
struct Terminals;

#ifndef NODE_H
#define NODE H

enum Directions {
    NORTH,
    EAST,
    SOUTH,
    WEST,
};

struct Node {
    Node* North = nullptr;
    Node* East = nullptr;
    Node* South = nullptr;
    Node* West = nullptr;
    bool visited = false;
};

//Returned linked-list path from start to end node
struct PathNode {
    Node* current;
    PathNode* next = nullptr;

    PathNode(Node* current) { this->current = current; }
};

//Pair of X Y integer values
struct Coordinates {
    short X;
    short Y;
    bool operator<(const Coordinates& other) const {
        if (X < other.X) return true;
        if (X > other.X) return false;
        return Y < other.Y;
    }
    Coordinates() {}
    Coordinates(short X, short Y) { this->X = X; this->Y = Y; }
};

#endif