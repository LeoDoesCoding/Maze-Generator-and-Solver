#include <iostream>
#include <map>
#include <random>
#include "../Headers/Maze.h"

using namespace std;
std::map<Coordinates, Node*> Maze::maze;
Coordinates Maze::dimensions{ 0,0 };
std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> Maze::bridges;
short Maze::mult;

void Maze::setDimensions(short x, short y) {
    dimensions.X = x;
    dimensions.Y = y;
}

//Generate random maze (of defined currently hard-coded dimensions)
void Maze::randomMaze() {
    setDimensions(8, 8);
    mult = 600/dimensions.Y;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, DIRECTIONS - 1);

    //Terminal nodes (start and end points)
    maze[{1, 1}] = new Node(mult);
    maze[{ dimensions.X, dimensions.Y }] = new Node(mult);
    maze[{1, 1}]->nodeShape.setPosition(mult, mult);
    maze[{dimensions.X, dimensions.Y}]->nodeShape.setPosition(mult, mult);

    Coordinates pointer = Coordinates(1, 1);
    Coordinates previous = Coordinates(1, 1);
    Directions direction;
    sf::RectangleShape bridge = sf::RectangleShape();


    while (!(pointer.X == dimensions.X && pointer.Y == dimensions.Y)) { //Attempt directions until not out-of-bounds
        direction = static_cast<Directions>(distrib(gen));
        switch (direction) {
        case NORTH:
            //If it is out of bounds, try again
            if (pointer.Y - 1 < 1) { continue; }

            pointer.Y -= 1;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->North == nullptr) {
                placeNode(pointer);

                bridge.setPosition(previous.X * mult, (previous.Y-0.4) * mult);
                bridge.setSize(sf::Vector2f(0.6*mult, mult*0.4));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->North = maze[pointer];
                maze[pointer]->South = maze[previous];
            }

            break;

        case EAST:
            //If it is out of bounds, try again
            if (pointer.X + 1 > dimensions.X) { continue; }

            pointer.X += 1;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->East == nullptr) {
                placeNode(pointer);

                bridge.setPosition((previous.X+0.6) * mult, previous.Y * mult);
                bridge.setSize(sf::Vector2f(0.4*mult, mult * 0.6));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->East = maze[pointer];
                maze[pointer]->West = maze[previous];
            }

            break;

        case SOUTH:
            //If it is out of bounds, try again
            if (pointer.Y + 1 > dimensions.Y) { continue; }

            pointer.Y += 1;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->South == nullptr) {
                placeNode(pointer);

                bridge.setPosition((previous.X) * mult, (previous.Y+0.6) * mult);
                bridge.setSize(sf::Vector2f(mult * 0.6, 0.4*mult));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->South = maze[pointer];
                maze[pointer]->North = maze[previous];
            }

            break;

        case WEST:
            //If it is out of bounds, try again
            if (pointer.X - 1 < 1) { continue; }

            pointer.X -= 1;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->West == nullptr) {
                placeNode(pointer);

                bridge.setPosition((previous.X-0.4) * mult, previous.Y * mult);
                bridge.setSize(sf::Vector2f(0.4*mult, mult * 0.6));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->West = maze[pointer];
                maze[pointer]->East = maze[previous];
            }

            break;
        }
        previous = pointer;
    }
    std::cout << "Finished." << endl;
}


void Maze::placeNode(Coordinates pointer) {
    if (maze.count(pointer) == 0) { //If there is no node in that space already, create a new one
        maze[pointer] = new Node(mult*0.6);
        maze[pointer]->nodeShape.setPosition(pointer.X * (mult), pointer.Y * (mult));
    }
}