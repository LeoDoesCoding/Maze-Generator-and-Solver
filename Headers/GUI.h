#pragma once
#include "Maze.h"
#include "Solver.h"
#include <SFML/Graphics.hpp>

class GUI {
public:
	static void setup();
	static void drawPath(Node* first, Node* second);

private:
	static void drawMaze();
	static Maze maze;
	static sf::RenderWindow window;
};