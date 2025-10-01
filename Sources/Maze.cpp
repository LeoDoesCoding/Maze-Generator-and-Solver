#include "../Headers/Maze.h"

using namespace std;

void Maze::setDimensions(short x, short y) {
    dimensions.X = x;
    dimensions.Y = y;
}

//Generate random maze (of defined currently hard-coded dimensions)
void Maze::randomMaze(short size) {
    setDimensions(size, size);

    //Starting node
    maze[{1, 1}] = new Node();

    gen1();
}

void Maze::resetSolver() {
    for (auto& space : maze) {
        space.second->visited = false;
    }
}

//Maze-generating algorithm 1
void Maze::gen1() {
    Coordinates pointer = Coordinates(1, 1);
    Coordinates previous = Coordinates(1, 1);
    Directions direction;
    short corridor;
    bool valid = true;
    auto it = maze.begin();


    while (!(pointer.X == dimensions.X && pointer.Y == dimensions.Y)) { //Attempt directions until not out-of-bounds
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
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.Y -= 1;
                if (maze[previous]->North == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                    }
                maze[previous]-> North = maze[pointer];
                maze[pointer]-> South = maze[previous];
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
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.X += 1;
                if (maze[previous]->East == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                    }
                    maze[previous]-> East = maze[pointer];
                    maze[pointer]-> West = maze[previous];
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
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.Y += 1;
                if (maze[previous]->South == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                    }
                    maze[previous]-> South = maze[pointer];
                    maze[pointer]-> North = maze[previous];
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
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.X -= 1;
                if (maze[previous]->West == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                    }
                maze[previous]-> West = maze[pointer];
                maze[pointer]-> East = maze[previous];
                }

                previous = pointer;
            }

            break;
        }
    }
}