#pragma once
#include <functional>
#include "Nodes.h"
#include "Maze.h"

class Solver {
public:
	static PathNode* DFS(Node* current, Node* goal);
};