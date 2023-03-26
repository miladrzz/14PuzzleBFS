# 14 Puzzle BFS

This application is a BFS AI pathfinding approach for a made up game called 14 puzzle.
There is a 4x4 matrix with random numbers in random places. and the goal is to sort them to become our desired matrix. for example :

4 3 11 12                                      1 2 3 4
1 6 2 10                                       5 6 7 8
0 14 5 7                     ------>           9 10 11 12
9 8 14 0                                       13 14 0 0

each number can be moved when there's a zero in upper, lower, left or right side of it, and it can be replaced with that.
this is a BFS approach for sloving this game.
