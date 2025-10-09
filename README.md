# Maze Generator & Solver [WIP, but working as intended]
SFML libraries for Graphics, System and Window must be setup in order to run the code in VS.

Todo:
 - Other maze-solving algorithms

 ## Project Parameters
 - Generates a graph of nodes with a maximum of 4 bi-directional connections of equal value/distance, constrained by coordinate placement on a 2D array.
    - There will always be a path from the start node to the end node.
    - Not every coordinate has to have a node.
 - Identifies a valid pathway.

  ### Future Developments
  - Add different algorithms for graph generation and path finding.
  - Identify path of shortest distance.

## Algorithms
### Maze Generation Algorithm (Gen1)
From a given starting coordinates, the first node is generated. Then, iterations occur to place nodes until the destination node is met. In each iteration, three values are generated at random:
 - Direction (NESW)
 - Already existing node
 - Corridor length (1-2)
 
Starting from the selected node, the path from here, in the direction selected and for the corridor length, a check is done to see if  any collision either with the boundaries of the maze OR with another node (unless that node is the last node of the corridor). If not, nodes are created, one for each corridor value, creating a bridge to the previous node. If the destination coordinates are collided with, it is bridged and no further nodes are places, regardless of corridor value.

**Advantages**
 - Mazes *always* have a path from start to end.
 - Usually generates rather full layout (not that I have yet established a quantifiale standard for this).

**Drawbacks**
 - Due to heavy reliance on RNG with no bias:
    - Probabilistic non-terminating.
    - A lot of invalid moves.
    - Maze complexity has no garuntee.
      - Solution path is usually a fairly predictable diagonal line.
    - Stupidly high iteration count for larger mazes (increased chances of invalid moves).

I appologies if the generator draws unfortunate patterns.