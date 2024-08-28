#pragma once
#include <iostream>
#include "../Headers/Solver.h"
#include "../Headers/GUI.h"
bool found = false;

using namespace std;

PathNode* Solver::DFS(Node* current, Node* goal) {
    sf::sleep(sf::seconds(0.1));
    current->visited = true;
    PathNode* pointer;
    PathNode* path = new PathNode(current);

    //Current node is destination
    if (current == goal) {
        found = true;
        return (path);
    }

    //If not, search each direction.
    if (current->North != nullptr && !current->North->visited) {
        GUI::drawPath(current, current->North);
        pointer = DFS(current->North, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->East != nullptr && !current->East->visited) {
        GUI::drawPath(current, current->East);
        pointer = DFS(current->East, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->South != nullptr && !current->South->visited) {
        GUI::drawPath(current, current->South);
        pointer = DFS(current->South, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->West != nullptr && !current->West->visited) {
        GUI::drawPath(current, current->West);
        pointer = DFS(current->West, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }
    return (path);
}