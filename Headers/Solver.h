#pragma once
#include "Nodes.h"
#include "GUI.h"
#include <iostream>

class Solver {
public:
	static PathNode* DFS(Coordinates location, Node* current, Node* goal);
	static bool found;
	
	//Current solution stats
	static int iterations;
	static int pathLength;
};