#pragma once
#include <SFML/Graphics.hpp>
struct Node;
struct PathNode;
struct Terminals;
#include <utility>

#ifndef NODE_H
#define NODE H
struct Node {
    short value;
    Node* North = nullptr;
    Node* East = nullptr;
    Node* South = nullptr;
    Node* West = nullptr;
    bool visited = false;

    //GUI properties
    sf::RectangleShape nodeShape;

    Node(short value) {
        this->value = value;
        nodeShape.setFillColor(sf::Color::White);
        nodeShape.setSize(sf::Vector2f(80.0f, 80.0f));
    }
};

//Returned linked-list path from start to end node
struct PathNode {
    Node* current;
    PathNode* next = nullptr;

    PathNode(Node* current) { this->current = current; }
};

//Starting from and endpoint
struct Terminals {
    Node* start;
    Node* end;
    Terminals(Node* start) { this->start = start; }
};

struct Coordinates {
    short X;
    short Y;
    bool operator<(const Coordinates& other) const {
        if (X < other.X) return true;
        if (X > other.X) return false;
        return Y < other.Y;
    }
    Coordinates(short X, short Y) { this->X = X; this->Y = Y; }
};

#endif