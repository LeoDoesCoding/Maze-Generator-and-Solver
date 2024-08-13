#pragma once
struct Node {
    short value;
    Node* North = nullptr;
    Node* East = nullptr;
    Node* South = nullptr;
    Node* West = nullptr;
    Node(short value) { this->value = value; }
};

//Returned linked-list path from start to end node
struct PathNode {
    Node* current;
    PathNode* next = nullptr;

    PathNode(Node* current) { this->current = current;  }
};

//Starting from and endpoint
struct Terminals {
    Node* start;
    Node* end;
    Terminals(Node* start) { this->start = start; }
};

Terminals* defaultMaze();
PathNode* DFS(Node* current, Node* end);
