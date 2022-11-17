//
// Created by Max Benson on 10/23/2021.
//

#ifndef MAZE_H
#define MAZE_H

bool SolveMaze(const Grid& maze, Stack<GridLocation>& solution, CursesWindow* pwindow = nullptr);
Set<GridLocation> GenerateValidMoves(const Grid& maze, const GridLocation& loc);
bool CheckSolution(const Grid& maze, Stack<GridLocation> path);

#endif //MAZE_H
