#include <iostream>
#include <map>
#include "../Headers/Maze.h"

using namespace std;
Terminals* Maze::points = nullptr;
std::map<Coordinates, Node*> Maze::maze;
Coordinates Maze::dimensions{ 0,0 };
std::map<std::pair<Coordinates, Coordinates>, sf::RectangleShape> Maze::bridges;


//Temporary maze generator. It's terrifying, but it is only transient.
void Maze::defaultMaze() {
    setDimensions(06, 04);
    sf::RectangleShape bridge = sf::RectangleShape(sf::Vector2f(50, 80));
    bridge.setPosition(150,100);
    bridges[make_pair(Coordinates{0,0}, Coordinates{0,1})] = bridge;

    points = new Terminals(new Node(1));
    Node* node2 = new Node(2);    Node* node3 = new Node(3);    Node* node4 = new Node(4);    Node* node5 = new Node(5);    Node* node6 = new Node(6);
    Node* node7 = new Node(7);    Node* node8 = new Node(8);    Node* node9 = new Node(9);    Node* node10 = new Node(10);    Node* node11 = new Node(11);
    Node* node12 = new Node(12);    Node* node13 = new Node(13);    Node* node14 = new Node(14);    Node* node15 = new Node(15);
    points->start->East = node2; points->start->South = node7;   maze[Coordinates{ 0, 0 }] = points->start;
    node2->East = node3;   node3->West = node2;  maze[Coordinates{ 1, 0 }] = node2;
    node3->East = node4;   node4->West = node3;  maze[Coordinates{ 2, 0 }] = node3;
    node4->East = node5; node4->South = node8;   node5->West = node4; node8->North = node4; maze[Coordinates{ 3, 0 }] = node4;
    node5->East = node6; node6->West = node5;   maze[Coordinates{ 4, 0 }] = node5;
    maze[Coordinates{ 5, 0 }] = node6;
    node7->South = node9; node9->South = node7;  maze[Coordinates{ 0, 1 }] = node7;
    node8->North = node4;  maze[Coordinates{ 3, 1 }] = node8;
    node9->East = node10; node9->South = node12; node10->West = node9; node12->North = node9;  maze[Coordinates{ 0, 2 }] = node9;
    node10->East = node11; node11->West = node10;  maze[Coordinates{ 1, 2 }] = node10;
    node11->South = node13; node13->North = node11; maze[Coordinates{ 2, 2 }] = node11;
    maze[Coordinates{ 0, 3 }] = node12;
    node13->East = node14; node14->West = node13;  maze[Coordinates{ 2, 3 }] = node13;
    node14->East = node15; node15->West = node14;  maze[Coordinates{ 3, 3 }] = node14;
    points->end = node15;  maze[Coordinates{ 4, 3 }] = node15;

    //Set location
    for (auto space : maze) {
        space.second->nodeShape.setPosition((space.first.X+1)*100, (space.first.Y+1)*100);
        /*(space.second->North != nullptr) {
            if (if (!bridges.contains((maze))))
            bridges.
        }
        if (space.second->East != nullptr) {
            space.second->nodeShape.move(-10, 0);
            space.second->nodeShape.scale(1.2, 1);
        }
        if (space.second->South != nullptr) {
            space.second->nodeShape.move(0, -10);
            space.second->nodeShape.scale(1, 1.2);
        }
        if (space.second->West != nullptr) {
            space.second->nodeShape.move(10, 0);
            space.second->nodeShape.scale(1.2, 1);
        }
        cout << "Done " << endl;*/
    }

}

void Maze::setDimensions(short x, short y) {
    dimensions.X = x;
    dimensions.Y = y;
}

//Oh boy
/*Terminals* randomMaze() {
    map<std::string, int> m;
    map <short, Node*> maze; //Coordinates 0000, Node
    short coord = 0000; //Starting coord (top left)

    //Loop x number of times
    //Choose NESW at random
    //Check it is within boundries

}*/