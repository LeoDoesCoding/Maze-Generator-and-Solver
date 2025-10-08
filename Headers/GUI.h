#pragma once
#include "Maze.h"
#include "Solver.h"
#include <SFML/Graphics.hpp>
#ifndef GUI_H
#define GUI H
static sf::Font font;
static sf::Color grey = sf::Color(100, 100, 100);

class textBox {
public:
	bool mode = false;
	std::string value = "5";

	textBox() {
		text.setString("5");
		text.setFont(font);
		box.setSize(sf::Vector2f(80, 30));
		box.setFillColor(grey);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(24);
	}

	void setMode(bool status) {
		mode = status;
		if (status) {
			box.setFillColor(sf::Color::White);
			text.setString(value + '|');
		} else {
			box.setFillColor(grey);
			if (value.length() == 0) {
				append('5');
			}
			text.setString(value);
		}
	}
	void setPosition(short x, short y) {
		box.setPosition(x, y);
		text.setPosition(x, y);
	}
	
	void append(char character) {
		value += character;
		text.setString(value + '|');
		if (std::stoi(value) > 20) {
			value = "20";
			text.setString(value + '|');
		}
	}

	void backSpace() {
		if (value.size() != 0) {
		value = value.substr(0, value.size()-1);
		text.setString(value + '|');
		}
	}

	int getSize() {
		return std::stoi(value);
	}
	sf::RectangleShape box;
	sf::Text text;
};


class GUI {
public:
	static void setup();
	static void update();
	static void drawBridge(Coordinates node, Directions direction);
private:
	static void disableInput();
	static void enableInput();

	static sf::RenderTexture canvas;
	static Maze maze;
	static sf::Text label;
	static sf::Text regenLabel;
	static sf::Text solverLabel;
	static sf::RenderWindow window;
	static textBox sizeBox;
	static sf::RectangleShape regenButton;
	static sf::RectangleShape solverButton;
	static sf::RectangleShape tile;

	static bool input;
	static int size;
	static PathNode* solution;
	static PathNode* mazePointer;
	static Coordinates UIpointer;
};

#endif