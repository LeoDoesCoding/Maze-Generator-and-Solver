#include "../Headers/GUI.h"

using namespace sf;
sf::RenderWindow GUI::window;
Maze GUI::maze;
sf::Text GUI::label;
textBox GUI::sizeBox;
sf::RectangleShape GUI::regenButton;
sf::RectangleShape GUI::solverButton;

int main() {
    GUI::setup();
    return 0;
};


void GUI::setup() {
    window.create(VideoMode(1000, 800), "Maze Solver");
    window.setKeyRepeatEnabled(false);
    srand(time(NULL));
    font.loadFromFile("Arial.ttf");

    sizeBox = textBox();
    sizeBox.setPosition(800, 140);
    label.setString("Size:");
    label.setFont(font);
    label.setCharacterSize(28);
    label.setPosition(800, 110);
    regenButton.setFillColor(sf::Color::Cyan);
    regenButton.setSize(sf::Vector2f(100, 30));
    regenButton.setPosition(800, 600);
    solverButton.setFillColor(sf::Color::Green);
    solverButton.setSize(sf::Vector2f(100, 30));
    solverButton.setPosition(800, 640);

    maze.randomMaze(std::stoi(sizeBox.getText()));
    window.display();
    drawMaze();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Num0) {
                    if (sizeBox.mode) { sizeBox.append('0'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num1) {
                    if (sizeBox.mode) { sizeBox.append('1'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num2) {
                    if (sizeBox.mode) { sizeBox.append('2'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num3) {
                    if (sizeBox.mode) { sizeBox.append('3'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num4) {
                    if (sizeBox.mode) { sizeBox.append('4'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num5) {
                    if (sizeBox.mode) { sizeBox.append('5'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num6) {
                    if (sizeBox.mode) { sizeBox.append('6'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num7) {
                    if (sizeBox.mode) { sizeBox.append('7'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num8) {
                    if (sizeBox.mode) { sizeBox.append('8'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Num9) {
                    if (sizeBox.mode) { sizeBox.append('9'); }
                } else if (event.key.scancode == sf::Keyboard::Scan::Backspace) {
                    if (sizeBox.mode) {
                        sizeBox.backSpace();
                    }
                } else if (event.key.scancode == sf::Keyboard::Scan::Enter) {
                    sizeBox.setMode(false);
                }
                drawMaze();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::FloatRect bounds = sizeBox.box.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    std::cout << "clicked" << std::endl;
                    sizeBox.setMode(true);
                    drawMaze();
                }

                //Regenerate button clicked
                bounds = regenButton.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    maze = Maze();
                    maze.randomMaze(std::stoi(sizeBox.getText()));
                    drawMaze();
                }

                //Solver button clicked
                bounds = solverButton.getGlobalBounds();
                if (bounds.contains(mouse)) {
                    Solver::found = false;
                    Solver::DFS(maze.getStart(), maze.getGoal());
                }

            }
        }
    }
}

void GUI::drawPath(Node* first, Node* second) {
    second->nodeShape.setFillColor(sf::Color::Green);
    maze.getBridge({ static_cast<short>(first->nodeShape.getPosition().x/maze.getMult()), static_cast<short>(first->nodeShape.getPosition().y / maze.getMult()) }, { static_cast<short>(second->nodeShape.getPosition().x / maze.getMult()), static_cast<short>(second->nodeShape.getPosition().y / maze.getMult()) }).setFillColor(sf::Color::Green);
    drawMaze();
}

void GUI::drawMaze() {
    window.clear();
    RectangleShape walls(sf::Vector2f(maze.getX() * maze.getMult(), maze.getY() * maze.getMult()));
    walls.setPosition(maze.getMult(), maze.getMult());
    walls.setFillColor(Color::Blue);
    window.draw(walls);
    for (auto& space : maze.getMaze()) {
        window.draw(space.second->nodeShape);
    }
    for (auto& bridge : maze.getBridges()) {
        window.draw(bridge.second);
    }

    window.draw(sizeBox.box);
    window.draw(label);
    window.draw(sizeBox.text);
    window.draw(regenButton);
    window.draw(solverButton);
    window.display();
}