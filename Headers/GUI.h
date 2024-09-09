#pragma once
#include "Maze.h"
#include "Solver.h"
#include <SFML/Graphics.hpp>
#ifndef GUI_H
#define GUI H
static sf::Font font;
#endif

class textBox {
public:
	sf::Color grey = sf::Color(100, 100, 100);

	textBox() {
		text.setString("5");
		text.setFont(font);
		mode = false;
		box.setSize(sf::Vector2f(80, 30));
		box.setFillColor(grey);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(24);
	}

	void setMode(bool status) { //if user has clicked button, enable typing
		mode = status;
		if (status) {
			box.setFillColor(sf::Color::White);
		} else {
			box.setFillColor(grey);
		}
	}
	void setPosition(short x, short y) {
		box.setPosition(x, y);
		text.setPosition(x, y);
	}
	std::string getText() { return text.getString(); }
	bool mode;
	void append(char character) {
		text.setString(text.getString() + character);
		if (std::stoi(getText()) > 20) {
			text.setString("20");
		}
	}
	void backSpace() { text.setString(text.getString().substring(0, text.getString().getSize() - 1));  }
	sf::RectangleShape box;
	sf::Text text;
};


class GUI {
public:
	static void setup();
	static void drawPath(Node* first, Node* second);

private:
	static void drawMaze();
	static Maze maze;
	static sf::Text label;
	static sf::RenderWindow window;
	static textBox sizeBox;
	static sf::RectangleShape regenButton;
	static sf::RectangleShape solverButton;
};