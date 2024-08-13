#include <iostream>
#include "Maze Solver.h"
bool found = false;

using namespace std;

int main() {
    Terminals* points = defaultMaze();
    PathNode* path = DFS(points->start, points->end);
    cout << "Finished" << endl;

    //Print final path from start to end points.
    cout << "Path from " << points->start->value << " to " << points->end->value << ":" << endl;
    for (PathNode* i = path; i != nullptr; i = i->next) {
        cout << i->current->value << ", ";
    }
}

//Temporary maze generator
Terminals* defaultMaze() {
    Terminals* toReturn = new Terminals(new Node(1));
    Node* node2 = new Node(2);    Node* node3 = new Node(3);    Node* node4 = new Node(4);    Node* node5 = new Node(5);    Node* node6 = new Node(6);
    Node* node7 = new Node(7);    Node* node8 = new Node(8);    Node* node9 = new Node(9);    Node* node10 = new Node(10);    Node* node11 = new Node(11);
    Node* node12 = new Node(12);    Node* node13 = new Node(13);    Node* node14 = new Node(14);    Node* node15 = new Node(15);
    toReturn->start->East = node2; toReturn->start->South = node7;
    node2->East = node3;
    node3->East = node4;
    node4->East = node5; node4->South = node8;
    node5->East = node6;
    node7->South = node9;
    node9->East = node10; node9->South = node12;
    node10->East = node11;
    node11->South = node13;
    node13->East = node14;
    node14->East = node15;
    toReturn->end = node15;

    return toReturn;
}

PathNode* DFS(Node * current, Node * end) {
    cout << "At node " << current->value << endl;
    PathNode* pointer;
    PathNode* path = new PathNode(current);

    //Current node is destination
    if (current == end) {
        found = true;
        return (path);
    }

    //If not, search each direction.
    if (current->North != nullptr) {
        pointer = DFS(current->North, end);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->East != nullptr) {
        pointer = DFS(current->East, end);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->South != nullptr) {
        pointer = DFS(current->South, end);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->West != nullptr) {
        pointer = DFS(current->West, end);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }
    return (path);
}