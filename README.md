# Maze 
A robot is asked to navigate a maze. It is placed at a certain position (the starting position) in the maze and is asked to try to reach another position (the goal position). Positions in the maze will either be open or blocked with an obstacle. Positions are identified by (x,y) coordinates.

At any given moment, the robot can only move 1 step in one of 4 directions. Valid moves are:

Go North: (x,y) -> (x,y-1)
Go East: (x,y) -> (x+1,y)
Go South: (x,y) -> (x,y+1)
Go West: (x,y) -> (x-1,y)
Note that positions are specified in zero-based coordinates (i.e., 0...size-1, where size is the size of the maze in the corresponding dimension).

The robot can only move to positions without obstacles and must stay within the maze.

The robot should search for a path from the starting position to the goal position (a solution path) until it finds one or until it exhausts all possibilities. In addition, it should mark the path it finds (if any) in the maze. 



Implement files from https://www.cs.bu.edu/teaching/alg/maze/
