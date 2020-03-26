# Recursive-Maze-Solver

The program accepts 5 arguments from the command-line: a ﬁle (which contains the environment); and 4 integers specifying start state and goal state, eg: <br/>
./robotplanner env.txt 0 2 4 1<br/>
would read the environment speciﬁcation from the ﬁle env.txt and should plan a path from [0 2] to goal state [4 1]. 

The environment is stored as text ﬁle in the following format: the ﬁrst line contains the width and height as two (space or tab separated) integers. Each subsequent line contains a set of space-or-tab-separated 0s and 1s, with 0 representing that a cell is free-space (and therefore navigable) and 1 indicating it is occupied, and therefore cannot be entered or passed through by the robot. For example<br/>
5 3 <br/>
0 0 1 0 0 <br/>
1 0 1 0 0 <br/>
0 0 0 0 1 <br/>
If we suppose that the start state is [0,0] (i.e. at the top left) and the goal state is [4,0] (i.e. top right), then a valid solutions is<br/>
R D D R R U U R<br/>
The ull output includes the number of nodes explored, the path length to the goal, followed by a line with the set of robot actions. For example:<br/>
20 8 <br/>
R D D R R U U R<br/>
If no path is possible then the program will output the following:<br/>
20 0 X<br/>
