#include "../Headers/Solver.h"

using namespace std;
bool Solver::found = false;
int Solver::iterations;
int Solver::pathLength;

PathNode* Solver::DFS(Coordinates location, Node* current, Node* goal) {
    sf::sleep(sf::seconds(0.05));
    current->visited = true;
    iterations++;
    PathNode* pointer;
    PathNode* path = new PathNode(current);
    GUI::update();

    //End if current node is destination
    if (current == goal) {
        found = true;
        return (path);
    }

    //Search each direction
    if (current->North != nullptr && !current->North->visited) {
        pointer = DFS({location.X, location.Y-1}, current->North, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->East != nullptr && !current->East->visited) {
        pointer = DFS({location.X+1, location.Y}, current->East, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->South != nullptr && !current->South->visited) {
        pointer = DFS({location.X, location.Y+1}, current->South, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }

    if (current->West != nullptr && !current->West->visited) {
        pointer = DFS({location.X-1, location.Y}, current->West, goal);
        if (found) {
            path->next = pointer;
            return (path);
        }
    }
    return (path);
}