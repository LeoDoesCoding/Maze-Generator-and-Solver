# Maze Generator & Solver [WIP]
SFML libraries for Graphics, System and Window must be setup in order to run the code in VS.

Todo:
 - Fix maze regeneration
 - Clean any code messes/optimise code
 - Add proper user interaction (ie, perameters etc)

## Algorithms
### Maze Generation Algorithm (Gen1)
From a given starting coordinates, the first node is generated. Then, iterations occur to place nodes until the destination node is met. In each iteration, three values are generated at random:
 - Direction (NESW)
 - Already existing node
 - Corridor length (1-3)
 
Starting from the selected node, the path from here, in the direction selected and for the corridor length, a check is done to see if  any collision either with the boundaries of the maze OR with another node (unless that node is the last node of the corridor). If not, nodes are created, one for each corridor value, creating a bridge to the previous node. If the destination coordinates are collided with, it is bridged and no further nodes are places, regardless of corridor value.

**Advantages**
 - Mazes *always* have a path from start to end.
 - Very maze-like, with dead ends and a rather full layout (not that there is a quantifiable standard for this, that I am aware of).

**Drawbacks**
 - High iteration count as there are lots of unusable collisions, thus generation is slow.
 - On average, the start->destination path is a fairly direct diagonal.
 - Sometimes draws some unfortunate patterns (sorry about that).