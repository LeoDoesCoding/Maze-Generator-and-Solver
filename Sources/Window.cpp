#include "../Headers/GUI.h"

using namespace sf;
sf::RenderWindow GUI::window;
Maze GUI::maze;
sf::Text GUI::label;
sf::Text GUI::regenLabel;
sf::Text GUI::solverLabel;
sf::Text GUI::mazeStats;
sf::Text GUI::solutionStats;
textBox GUI::sizeBox;
sf::RectangleShape GUI::regenButton;
sf::RectangleShape GUI::solverButton;
sf::RectangleShape GUI::tile;
bool GUI::input;
int GUI::size;
PathNode* GUI::solution;
PathNode* GUI::mazePointer;
Coordinates GUI::UIpointer;

int main() {
    GUI::setup();
    return 0;
};


void GUI::setup() {
    window.create(VideoMode(1140, 770), "Maze Solver");
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
    regenButton.setSize(sf::Vector2f(180, 40));
    regenButton.setPosition(730,660);
    regenLabel.setString("Generate");
    regenLabel.setFont(font);
    regenLabel.setColor(sf::Color::Black);
    regenLabel.setPosition(760, 660);

    //Solver Button
    solverButton.setFillColor(sf::Color::Green);
    solverButton.setSize(sf::Vector2f(180, 40));
    solverButton.setPosition(930, 660);
    solverLabel.setString("Solve");
    solverLabel.setFont(font);
    solverLabel.setColor(sf::Color::Black);
    solverLabel.setPosition(980, 660);

    //Satistics
    mazeStats.setColor(sf::Color::Cyan);
    mazeStats.setPosition(20, 710);
    mazeStats.setFont(font);
    mazeStats.setCharacterSize(20);
    solutionStats.setColor(sf::Color::Green);
    solutionStats.setPosition(20, 730);
    solutionStats.setFont(font);
    solutionStats.setCharacterSize(20);

    maze.randomMaze(5);
    setMazeStats();
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
                    solution = nullptr;
                    maze = Maze();
                    maze.randomMaze(size);
                    setMazeStats();
                    update();
                }

                //Solver button clicked
                bounds = solverButton.getGlobalBounds();
                if (bounds.contains(mouse) && input) {
                    maze.resetSolver();
                    GUI::disableInput();
                    Solver::found = false;
                    Solver::iterations = 0;
                    solution = Solver::DFS({1,1}, maze.getStart(), maze.getGoal());
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
        tile.setFillColor(Color::Yellow);
    } else {
        tile.setFillColor(Color::White);
    }

    tile.setSize(sf::Vector2f(510/size, 510/size));
    tile.setPosition((space.first.X * 680 - 595) / size + 20, (space.first.Y * 680 - 595) / size + 20);
    window.draw(tile);

    //Draw bridges
    if (space.second->visited) {
        tile.setFillColor(Color::Yellow);
    } else {
        tile.setFillColor(Color::White);
    }
    tile.setPosition((space.first.X * 680 - 595) / size + 20, (space.first.Y * 680 - 595) / size + 20);
    window.draw(tile);

    if (space.second->East) {
        if (space.second->East->visited && space.second->visited) {
            tile.setFillColor(Color::Yellow);
        } else {
            tile.setFillColor(Color::White);
        }
        drawBridge(space.first, EAST);
    }
    if (space.second->South) {
        if (space.second->South->visited && space.second->visited) {
            tile.setFillColor(Color::Yellow);
        } else {
            tile.setFillColor(Color::White);
        }
        drawBridge(space.first, SOUTH);
    }
    }

    //Draw solved path (if applicable)
    if (solution != nullptr) {
        tile.setFillColor(Color::Green);
        UIpointer = {1, 1};
        mazePointer = solution;
        Solver::pathLength = 0;
        while (mazePointer != nullptr) {
            Solver::pathLength++;
            tile.setSize(sf::Vector2f(510/size, 510/size));
            tile.setPosition((UIpointer.X * 680 - 595) / size + 20, (UIpointer.Y * 680 - 595) / size + 20);
            window.draw(tile);

            //Move UI pointer
            if (mazePointer->next != nullptr) {
                if (mazePointer->current->North == mazePointer->next->current) {
                    drawBridge(UIpointer, NORTH);
                    UIpointer = {UIpointer.X, UIpointer.Y-1};
                } else if (mazePointer->current->East == mazePointer->next->current) {
                    drawBridge(UIpointer, EAST);
                    UIpointer = {UIpointer.X+1, UIpointer.Y};
                } else if (mazePointer->current->South == mazePointer->next->current) {
                    drawBridge(UIpointer, SOUTH);
                    UIpointer = {UIpointer.X, UIpointer.Y+1};
                } else if (mazePointer->current->West == mazePointer->next->current) {
                    drawBridge(UIpointer, WEST);
                    UIpointer = {UIpointer.X-1, UIpointer.Y};
                }
            }

            mazePointer = mazePointer->next;
        }
        std::ostringstream sSS;
        sSS << "Iterations: " << Solver::iterations <<
        "   Solution path length: " << Solver::pathLength;
        solutionStats.setString(sSS.str());
    }

    window.draw(sizeBox.box);
    window.draw(label);
    window.draw(sizeBox.text);
    window.draw(regenButton);
    window.draw(solverButton);
    window.draw(regenLabel);
    window.draw(solverLabel);
    window.draw(solutionStats);
    window.draw(mazeStats);
    window.display();
}

void GUI::drawBridge(Coordinates node, Directions direction) {
    switch (direction) {
        case NORTH:
            tile.setSize(sf::Vector2f(510/size, 170/size+1));
            tile.setPosition((node.X * 680 - 595) / size + 20, (node.Y * 680 - 765) / size + 20);
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
            tile.setPosition((node.X * 680 - 765) / size + 20, (node.Y * 680 - 595) / size + 20);
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

void GUI::setMazeStats() {
    std::ostringstream msSS;
    msSS << "Iterations: " << maze.iterations <<
    "   Occupied tiles: " << maze.occupied << "\/" << (size * size) <<
    "   Connections: " << maze.connections << "\/" << (size * size + 2 * size - 1);
    mazeStats.setString(msSS.str());
}