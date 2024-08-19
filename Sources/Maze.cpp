#include <iostream>
#include <map>
#include "../Headers/Maze.h"
#include <random>

using namespace std;
std::map<Coordinates, Node*> Maze::maze;
Coordinates Maze::dimensions{ 0,0 };
std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> Maze::bridges;

void Maze::setDimensions(short x, short y) {
    dimensions.X = x;
    dimensions.Y = y;
}

//Generate random maze (of defined currently hard-coded dimensions)
void Maze::randomMaze() {
    setDimensions(6, 4);
    //Terminal nodes (start and end points)
    maze[{1, 1}] = new Node();
    maze[{ dimensions.X, dimensions.Y }] = new Node();
    maze[{1, 1}]->nodeShape.setPosition(100, 100);
    maze[{dimensions.X, dimensions.Y}]->nodeShape.setPosition(dimensions.X*100,  dimensions.Y*100);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, DIRECTIONS - 1);
    Coordinates pointer = Coordinates(1, 1);
    Coordinates previous = Coordinates(1, 1);

    Directions direction;
    sf::RectangleShape bridge = sf::RectangleShape();


    while (!(pointer.X == dimensions.X && pointer.Y == dimensions.Y)) { //Attempt directions until not out-of-bounds
        direction = static_cast<Directions>(distrib(gen));
        switch (direction) {
        case NORTH:
            if (pointer.Y - 1 < 1) { //If it is out of bounds, try again
                std::cout << "Out of bounds." << endl;
                continue;
            }
            pointer.Y -= 1;
            std::cout << "previous: " << previous.X << ", " << previous.Y << ". Pointe: " << pointer.X << ", " << pointer.Y << endl;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->North == nullptr) {
                if (maze.count(pointer) == 0) { //If there is no node in that space already, create a new one
                    maze[pointer] = new Node();
                    maze[pointer]->nodeShape.setPosition(pointer.X * 100, pointer.Y * 100);
                    std::cout << "No node here, let's put new one" << endl;
                }

                bridge.setPosition(previous.X * 100, (previous.Y-0.2) * 100);
                bridge.setSize(sf::Vector2f(80, 20));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->North = maze[pointer];
                maze[pointer]->South = maze[previous];
            }

            break;
        case EAST:
            if (pointer.X + 1 > dimensions.X) { //If it is out of bounds, try again
                std::cout << "Out of bounds." << endl;
                continue;
            }
            pointer.X += 1;
            std::cout << "previous: " << previous.X << ", " << previous.Y << ". Pointe: " << pointer.X << ", " << pointer.Y << endl;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->East == nullptr) {
                if (maze.count(pointer) == 0) { //If there is no node in that space already, create a new one
                    maze[pointer] = new Node();
                    maze[pointer]->nodeShape.setPosition(pointer.X * 100, pointer.Y * 100);
                    std::cout << "No node here, let's put new one" << endl;
                }

                bridge.setPosition((previous.X+0.8) * 100, previous.Y * 100);
                bridge.setSize(sf::Vector2f(20, 80));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->East = maze[pointer];
                maze[pointer]->West = maze[previous];
            }

            break;
        case SOUTH:
            if (pointer.Y + 1 > dimensions.Y) { //If it is out of bounds, try again
                std::cout << "Out of bounds." << endl;
                continue;
            }
            pointer.Y += 1;
            std::cout << "previous: " << previous.X << ", " << previous.Y << ". Pointe: " << pointer.X << ", " << pointer.Y << endl;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->South == nullptr) {
                if (maze.count(pointer) == 0) { //If there is no node in that space already, create a new one
                    maze[pointer] = new Node();
                    maze[pointer]->nodeShape.setPosition(pointer.X * 100, pointer.Y * 100);
                    std::cout << "No node here, let's put new one" << endl;
                }

                bridge.setPosition((previous.X) * 100, (previous.Y+0.8) * 100);
                bridge.setSize(sf::Vector2f(80, 20));
                bridges[make_pair(pointer, previous)] = bridge;

                maze[previous]->South = maze[pointer];
                maze[pointer]->North = maze[previous];
            }

            break;
        case WEST:
            if (pointer.X - 1 < 1) { //If it is out of bounds, try again
                std::cout << "Out of bounds." << endl;
                continue;
            }
            pointer.X -= 1;
            std::cout << "previous: " << previous.X << ", " << previous.Y << ". Pointe: " << pointer.X << ", " << pointer.Y << endl;

            //Has not been traversed yet. Create bridge.
            if (maze[previous]->West == nullptr) {
                if (maze.count(pointer) == 0) { //If there is no node in that space already, create a new one
                    maze[pointer] = new Node();
                    maze[pointer]->nodeShape.setPosition(pointer.X * 100, pointer.Y * 100);
                    std::cout << "No node here, let's put new one" << endl;
                }

                bridge.setPosition((previous.X-0.2) * 100, previous.Y * 100);
                bridge.setSize(sf::Vector2f(20, 80));
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