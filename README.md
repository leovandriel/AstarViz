AstarViz
========

*Visualizes various pathfinding algorithms.*

About
-----
AstarViz is a small graduation side-project to better understand the performance of various path search algorithms

The program generates a pseudo random graph based on a given node and edge density, and a randomizer seed. Next, given a start and end node, a graph search is performed using the selected search algorithm and configuration. Finally the resulting path and final search state is drawn onto the canvas.

Usage
-----
The program updates the entire graph search after each modification in the GUI. To select the start and end node, use respectively the left and right mouse button to click on the canvas. Use the 'Randomize', 'Node count', and 'Edge density' spinner to configure the graph generation. Use the 'Algorithm' combo to select on of the following algorithms:

- 'Breadth', expand nodes FIFO style, no sorting (queue).
- 'Depth', expand nodes LIFO style, using only per node heuristic sort (stack).
- 'Nearest', expand node with smallest heuristic (queue).
- 'A*Heap', A* using a slow heap sort (vector heap).
- 'A*List', A* using an optimized linked list (linked list).

The last three algorithms use a heuristics to direct their search. This heuristic can be controlled by the 'Optimality' parameter, which multiplies the standard Euclidean. A number of standard graph search specs are provided:

- 'Found', indicates path existence.
- 'Time', the time (ms) needed to run the algorithm.
- 'Node Expand', the number of nodes that were visited by the graph search.
- 'Max Loop', the number of iterations in the most nested loop.
- 'Est Length', the path length according to the heuristic.
- 'Length', the path length measured from node to node.
- 'Nodes', the number of nodes in the path.

The following additional statistics are provided:

- 'NodeExp / ms', Number of nodes visited per millisecond.
- 'SuccExp / ms', Number of successor that were expanded per millisecond.
- 'SuccExp / NodeExp', Ratio of successor expansion and nodes visited.
- 'NodesSq / NodeExp', Ratio of the square of the number of nodes in the paths and the number of nodes visited.
- 'NodesSq / SuccExp', Ratio of the square of the number of nodes in the paths and the number of successors expanded.

Nodes are colored according to their search status:

- Orange, on the path..
- Blue, visited or closed.
- Pink, queued or open.
- Green, start.
- Red, end.
- Gray, unvisited.

Build
-----
AstarViz can be compiled using the 'AstarViz.vcproj' Visual Studio project file. Make sure wxWidgets libraries are present ([www.wxWidgets.org](http://www.wxwidgets.org/)) and the 'WXWIN' global variable directs to the main wxWidgets installation folder. To edit the GUI design, use the 'AstarViz.fbp' FormBuilder file ([www.wxFormBuilder.org](http://www.wxformbuilder.org/)).

License
-------
AstarViz is licensed under the terms of the GNU General Public License, see the included LICENSE file.

Author
------
[Leo Vandriel](http://www.leovandriel.com)