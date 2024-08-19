#include <iostream>
#include "../Headers/Solver.h"
bool found = false;

using namespace std;

/*PathNode* Solver::DFS(Node* current) {
    current->visited = true;
    PathNode* pointer;
    PathNode* path = new PathNode(current);

    //Current node is destination
    if (current == Maze::getDestination()) {
        found = true;
        return (path);
    }

    //If not, search each direction.
    if (current->North != nullptr && !current->North->visited) {
        pointer = DFS(current->North);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->East != nullptr && !current->East->visited) {
        pointer = DFS(current->East);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->South != nullptr && !current->South->visited) {
        pointer = DFS(current->South);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->West != nullptr && !current->West->visited) {
        pointer = DFS(current->West);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }
    return (path);
}*/