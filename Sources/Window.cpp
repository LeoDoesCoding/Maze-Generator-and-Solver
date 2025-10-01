#include "../Headers/GUI.h"

using namespace sf;
sf::RenderWindow GUI::window;
Maze GUI::maze;
sf::Text GUI::label;
sf::Text GUI::regenLabel;
sf::Text GUI::solverLabel;
textBox GUI::sizeBox;
sf::RectangleShape GUI::regenButton;
sf::RectangleShape GUI::solverButton;
sf::RectangleShape GUI::tile;
bool GUI::input;
int GUI::size;

int main() {
    GUI::setup();
    return 0;
};


void GUI::setup() {
    window.create(VideoMode(1000, 750), "Maze Solver");
    window.setKeyRepeatEnabled(false);
    srand(time(NULL));
    font.loadFromFile("Arial.ttf");
    input = true;
    size = 5;

    label.setString("Generation: 1\nSize:");
    label.setFont(font);
    label.setCharacterSize(28);
    label.setPosition(720, 20);

    //Size Box
    sizeBox = textBox();
    sizeBox.setPosition(800, 55);

    //Regenerate Button
    regenButton.setFillColor(sf::Color::Cyan);
    regenButton.setSize(sf::Vector2f(200, 40));
    regenButton.setPosition(750,590);
    regenLabel.setString("Generate");
    regenLabel.setFont(font);
    regenLabel.setColor(sf::Color::Black);
    regenLabel.setPosition(790, 590);

    //Solver Button
    solverButton.setFillColor(sf::Color::Green);
    solverButton.setSize(sf::Vector2f(200, 40));
    solverButton.setPosition(750, 660);
    solverLabel.setString("Solve");
    solverLabel.setFont(font);
    solverLabel.setColor(sf::Color::Black);
    solverLabel.setPosition(810, 660);

    maze.randomMaze(5);
    update();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && sizeBox.mode) {
                if (event.key.scancode == sf::Keyboard::Scan::Num0) {
                    sizeBox.append('0');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num1) {
                    sizeBox.append('1');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num2) {
                    sizeBox.append('2');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num3) {
                    sizeBox.append('3');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num4) {
                    sizeBox.append('4');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num5) {
                    sizeBox.append('5');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num6) {
                    sizeBox.append('6');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num7) {
                    sizeBox.append('7');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num8) {
                    sizeBox.append('8');
                } else if (event.key.scancode == sf::Keyboard::Scan::Num9) {
                    sizeBox.append('9');
                } else if (event.key.scancode == sf::Keyboard::Scan::Backspace) {
                        sizeBox.backSpace();
                } else if (event.key.scancode == sf::Keyboard::Scan::Enter) {
                    sizeBox.setMode(false);
                }
                update();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && input) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                //Size setter box clicked
                sf::FloatRect bounds = sizeBox.box.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    sizeBox.setMode(true);
                    update();
                } else {
                    if (sizeBox.mode) {
                        sizeBox.setMode(false); 
                        update();
                    }
                }

                //Regenerate button clicked
                bounds = regenButton.getGlobalBounds();
                if (bounds.contains(mouse) && input) {
                    size = sizeBox.getSize();
                    maze = Maze();
                    maze.randomMaze(size);
                    update();
                }

                //Solver button clicked
                bounds = solverButton.getGlobalBounds();
                if (bounds.contains(mouse) && input) {
                    maze.resetSolver();
                    Solver::found = false;
                    GUI::disableInput();
                    Solver::DFS({1,1}, maze.getStart(), maze.getGoal());
                    GUI::enableInput();
                }

            }
        }
    }
}

void GUI::update() {
    window.clear();
    RectangleShape walls(sf::Vector2f(680, 680));
    walls.setPosition(20, 20);
    walls.setFillColor(Color::Blue);
    window.draw(walls);

    //Draw nodes
    tile.setSize(sf::Vector2f(510/size, 510/size));
    for (auto& space : maze.getMaze()) {
    if (space.second->visited) {
        tile.setFillColor(Color::Green);
    } else {
        tile.setFillColor(Color::White);
    }

    tile.setSize(sf::Vector2f(510/size, 510/size));
    tile.setPosition((space.first.X * 680 - 595) / size + 20, (space.first.Y * 680 - 595) / size + 20);
    window.draw(tile);

    //Draw bridges
    if (space.second->visited) {
        tile.setFillColor(Color::Green);
    } else {
        tile.setFillColor(Color::White);
    }
    tile.setPosition((space.first.X * 680 - 595) / size + 20, (space.first.Y * 680 - 595) / size + 20);
    window.draw(tile);

    if (space.second->East) {
        drawBridge(space.first, EAST, (space.second->East->visited && space.second->visited));
    }
    if (space.second->South) {
        drawBridge(space.first, SOUTH, (space.second->South->visited && space.second->visited));
    }
    }

    window.draw(sizeBox.box);
    window.draw(label);
    window.draw(sizeBox.text);
    window.draw(regenButton);
    window.draw(solverButton);
    window.draw(regenLabel);
    window.draw(solverLabel);
    window.display();
}

void GUI::drawBridge(Coordinates node, Directions direction, bool traversed) {
    if (traversed) {
        tile.setFillColor(Color::Green);
    } else {
        tile.setFillColor(Color::White);
    }

    switch (direction) {
        case NORTH:
            tile.setSize(sf::Vector2f(510/size, 170/size+1));
            tile.setPosition((node.Y * 680 - 85) / size + 20, (node.X * 680 - 595) / size + 20);
            break;
        case EAST:
            tile.setSize(sf::Vector2f(170/size+1, 510/size));
            tile.setPosition((node.X * 680 - 85) / size + 20, (node.Y * 680 - 595) / size + 20);
            break;
        case SOUTH:
            tile.setSize(sf::Vector2f(510/size, 170/size+1));
            tile.setPosition((node.X * 680 - 595) / size + 20, (node.Y * 680 - 85) / size + 20);
            break;
        case WEST:
            tile.setSize(sf::Vector2f(170/size+1, 510/size));
            tile.setPosition((node.Y * 680 - 595) / size + 20, (node.X * 680 - 85) / size + 20);
            break;
    }

    window.draw(tile);
}

void GUI::disableInput() {
    sizeBox.setMode(false);
    regenButton.setFillColor(grey);
    solverButton.setFillColor(grey);
}

void GUI::enableInput() {
    regenButton.setFillColor(sf::Color::Cyan);
    solverButton.setFillColor(sf::Color::Green);
    update();
}