#pragma once
#include "Nodes.h"
#include "GUI.h"
#include <iostream>

class Solver {
public:
	static PathNode* DFS(Node* current, Node* goal);
	static bool found;
};