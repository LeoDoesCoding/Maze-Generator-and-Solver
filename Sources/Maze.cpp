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
    iterations = 0;
    occupied = 1;


    while (!(pointer.X == dimensions.X && pointer.Y == dimensions.Y)) { //Attempt directions until not out-of-bounds
        iterations++;
        direction = Directions(rand() % 4);
        cout <<"DIRECTION: " << direction;
        corridor = short(rand() % 1) + 1;
        valid = true;
        it = maze.begin();
        advance(it, rand() % maze.size());
        pointer = it->first;
        previous = it->first;

        switch (direction) {
        case NORTH:
        std::cout<<" - North" <<endl;
            for (short i = 0; i < corridor; i++) {
                //Goal node found (bottom right node)
                if (pointer.X == dimensions.X && pointer.Y - i - 1 == dimensions.Y) {
                    break;
                }

                //Retry if either: out of bounds OR collides with another node
                if (pointer.Y - i - 1 == 0 || (maze.count({ pointer.X, short(pointer.Y - i - 1) }) != 0 && i != corridor)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) { std::cout<<iterations<<" OUFF"<<std::endl;continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.Y -= 1;
                if (maze[previous]->North == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                        occupied++;
                    }
                maze[previous]-> North = maze[pointer];
                maze[pointer]-> South = maze[previous];
                connections++;
                }
                previous = pointer;
                std::cout<< iterations << " freakin sweet"<<std::endl;
            }

            break;

        case EAST:
        std::cout<<" - East" <<endl;
            //Attempt coridoor
            for (short i = 0; i < corridor; i++) {
                //Goal node found (bottom right node)
                if (pointer.X + i + 1 == dimensions.X && pointer.Y == dimensions.Y) {
                    break;
                }

                //Retry if either: out of bounds OR collides with another node
                if (pointer.X + i + 1 > dimensions.X || (maze.count({ short(pointer.X + i + 1), pointer.Y }) != 0 && i != corridor)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) { std::cout<<iterations<<" OUFF"<<std::endl;continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.X += 1;
                if (maze[previous]->East == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                        occupied++;
                    }
                    maze[previous]-> East = maze[pointer];
                    maze[pointer]-> West = maze[previous];
                    connections++;
                }
                
                previous = pointer;
                std::cout<< iterations << " freakin sweet"<<std::endl;
            }

            break;

        case SOUTH:
        std::cout<<" - South" <<endl;
            //Attempt coridoor
            for (short i = 0; i < corridor; i++) {
                //Goal node found (bottom right node)
                if (pointer.X == dimensions.X && pointer.Y + i + 1 == dimensions.Y) {
                    break;
                }

                //Retry if either: out of bounds OR collides with another node
                if (pointer.Y + i + 1 > dimensions.Y || (maze.count({ pointer.X, short(pointer.Y + i + 1) }) != 0 && i != corridor)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) { std::cout<<iterations<<" OUFF"<<std::endl;continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.Y += 1;
                if (maze[previous]->South == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                        occupied++;
                    }
                    maze[previous]-> South = maze[pointer];
                    maze[pointer]-> North = maze[previous];
                    connections++;
                }
                previous = pointer;
                std::cout<< iterations << " freakin sweet"<<std::endl;
            }

            break;

        case WEST:
        std::cout<<" - North" <<endl;
            //Attempt coridoor
            for (short i = 0; i < corridor; i++) {
                //Goal node found (bottom right node)
                if (pointer.X - i - 1 == dimensions.X && pointer.Y == dimensions.Y) {
                    break;
                }

                //Retry if either: out of bounds OR collides with another node
                if (pointer.X - i - 1 == 0 || (maze.count({ short(pointer.X - i - 1), pointer.Y }) != 0 && i != corridor)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) { std::cout<<iterations<<" OUFF"<<std::endl;continue; }

            //Create nodes
            for (short i = 0; i < corridor; i++) {
                pointer.X -= 1;
                if (maze[previous]->West == nullptr) {
                    if (maze.count(pointer) == 0) {
                        maze[pointer] = new Node();
                        occupied++;
                    }
                maze[previous]-> West = maze[pointer];
                maze[pointer]-> East = maze[previous];
                connections++;
                }

                previous = pointer;
            }
            std::cout<< iterations << " freakin sweet"<<std::endl;

            break;
        }
    }
}