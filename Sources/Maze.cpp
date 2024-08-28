#include <iostream>
#include <map>
#include <random>
#include "../Headers/Maze.h"

using namespace std;

void Maze::setDimensions(short x, short y) {
    dimensions.X = x;
    dimensions.Y = y;
}

//Generate random maze (of defined currently hard-coded dimensions)
void Maze::randomMaze() {
    setDimensions(7, 7);
    mult = 600 / dimensions.Y;

    //Terminal nodes (start and end points)
    maze[{1, 1}] = new Node(mult);
    maze[{1, 1}]->nodeShape.setPosition(mult, mult);
    maze[{1, 1}]->nodeShape.setFillColor(sf::Color::Green);

    gen1();
}

//Maze-generating algorithm 1
void Maze::gen1() {
    Coordinates pointer = Coordinates(1, 1);
    Coordinates previous = Coordinates(1, 1);
    Directions direction;
    short corridor;
    bool valid = true;
    auto it = maze.begin();
    short iteration = 0;


    while (!(pointer.X == dimensions.X && pointer.Y == dimensions.Y)) { //Attempt directions until not out-of-bounds
        //cout << "Iteration " << iteration << endl;
        iteration++;
        direction = Directions(rand() % 4);
        corridor = short(rand() % 2);
        valid = true;
        it = maze.begin();
        advance(it, rand() % maze.size());
        pointer = it->first;
        previous = it->first;

        switch (direction) {
        case NORTH:
            //Retry if either: out of bounds OR collides with another node
            for (short i = 0; i < corridor; i++) {
                if (pointer.X == dimensions.X && pointer.Y - i - 1 == dimensions.Y) {
                    break;
                }
                if (pointer.Y - i - 1 == 0 || (maze.count({ pointer.X, short(pointer.Y - i - 1) }) != 0 && i != corridor)) {
                    //cout << "Out of bounds" << endl;
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.Y -= 1;
                if (maze[previous]->North == nullptr) {
                    placeNode(pointer, previous, NORTH);
                }
                previous = pointer;
            }

            break;

        case EAST:
            //Retry if either: out of bounds OR collides with another node
            for (short i = 0; i < corridor; i++) {
                if (pointer.X + i + 1 == dimensions.X && pointer.Y == dimensions.Y) {
                    break;
                }
                if (pointer.X + i + 1 > dimensions.X || (maze.count({ short(pointer.X + i + 1), pointer.Y }) != 0 && i != corridor)) {
                    //cout << "Out of bounds" << endl;
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.X += 1;
                if (maze[previous]->East == nullptr) {
                    placeNode(pointer, previous, EAST);
                }
                previous = pointer;
            }

            break;

        case SOUTH:
            //Retry if either: out of bounds OR collides with another node
            for (short i = 0; i < corridor; i++) {
                if (pointer.X == dimensions.X && pointer.Y + i + 1 == dimensions.Y) {
                    break;
                }
                if (pointer.Y + i + 1 > dimensions.Y || (maze.count({ pointer.X, short(pointer.Y + i + 1) }) != 0 && i != corridor)) {
                    //cout << "Out of bounds" << endl;
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.Y += 1;
                if (maze[previous]->South == nullptr) {
                    placeNode(pointer, previous, SOUTH);
                }
                previous = pointer;
            }

            break;

        case WEST:
            //Retry if either: out of bounds OR collides with another node
            for (short i = 0; i < corridor; i++) {
                if (pointer.X - i - 1 == dimensions.X && pointer.Y == dimensions.Y) {
                    break;
                }
                if (pointer.X - i - 1 == 0 || (maze.count({ short(pointer.X - i - 1), pointer.Y }) != 0 && i != corridor)) {
                    //cout << "Out of bounds" << endl;
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.X -= 1;
                if (maze[previous]->West == nullptr) {
                    placeNode(pointer, previous, WEST);
                }
                previous = pointer;
            }

            break;
        }
        //cout << "Next" << endl;
    }
    std::cout << "Finished." << endl;
}

/*void Maze::gen2() {
    random_device rd;
    mt19937 g(rd());

    shuffle(directions, directions + sizeof(directions) / sizeof(directions[0]), g);
}*/


void Maze::placeNode(Coordinates pointer, Coordinates previous, Directions direction) {
    sf::RectangleShape bridge = sf::RectangleShape();
    if (maze.count(pointer) == 0) { //If there is no node in that space already, create a new one
        maze[pointer] = new Node(mult * 0.6);
        maze[pointer]->nodeShape.setPosition(pointer.X * (mult), pointer.Y * (mult));
    }

    switch (direction) {
    case NORTH:
        bridge.setPosition(previous.X * mult, (previous.Y - 0.4) * mult);
        bridge.setSize(sf::Vector2f(0.6 * mult, mult * 0.4));
        bridges[make_pair(pointer, previous)] = bridge;

        maze[previous]->North = maze[pointer];
        maze[pointer]->South = maze[previous];
        break;
    case EAST:
        bridge.setPosition((previous.X + 0.6) * mult, previous.Y * mult);
        bridge.setSize(sf::Vector2f(0.4 * mult, mult * 0.6));
        bridges[make_pair(pointer, previous)] = bridge;

        maze[previous]->East = maze[pointer];
        maze[pointer]->West = maze[previous];
        break;
    case SOUTH:
        bridge.setPosition((previous.X) * mult, (previous.Y + 0.6) * mult);
        bridge.setSize(sf::Vector2f(mult * 0.6, 0.4 * mult));
        bridges[make_pair(pointer, previous)] = bridge;

        maze[previous]->South = maze[pointer];
        maze[pointer]->North = maze[previous];
        break;
    case WEST:
        bridge.setPosition((previous.X - 0.4) * mult, previous.Y * mult);
        bridge.setSize(sf::Vector2f(0.4 * mult, mult * 0.6));
        bridges[make_pair(pointer, previous)] = bridge;

        maze[previous]->West = maze[pointer];
        maze[pointer]->East = maze[previous];
        break;
    }
}