//
// Maze solution
// Author: Max Benson
// Date: 08/16/2021
//

#include "Grid.h"
#include "Stack.h"
#include "Queue.h"
#include "Set.h"
#include "CursesWindow.h"
#include "Maze.h"

/**
* Attempt to solve the maze using a breadth first algorithm
* @param maze the maze that we want to solve
* @param solution out parameter used to return solution if it is found
* @param pwindow if not nullptr, used to animate the solution process
* @return true if solution can be found, false otherwise
*/
bool SolveMaze(const Grid& maze, Stack<GridLocation>& solution, CursesWindow* pwindow) {
    Queue<Stack<GridLocation>> solutionsToTest;
    Set<GridLocation> locationsVisited;

    // Testing if the upper left point of the maze, the starting point, is a wall or not.
    GridLocation loc = GridLocation(0,0);
    if (maze[loc] == false) {
        return false;
    }

    locationsVisited.Add(loc);
    Stack<GridLocation> tempStack;
    tempStack.Push(loc);

    while (!solutionsToTest.IsEmpty()) {
        Set<GridLocation> possibleMoves;

        tempStack = solutionsToTest.Dequeue();

        possibleMoves = GenerateValidMoves(maze, tempStack.Peek());

        for (size_t i = 0; i < possibleMoves.Size(); i++) {

            // If one of the possible moves is already visited by another path, don't continue.
            if (locationsVisited.Contains(possibleMoves.Get(i))) { // Does this line work??
                continue;
            }

            Stack<GridLocation> newStack;
            newStack = tempStack;
            newStack.Push(possibleMoves.Get(i));
            locationsVisited.Add(possibleMoves.Get(i));

            // Testing if the current possible move is the bottom right of the maze. If so, return true and set solution to the correct solution.
            if ( (possibleMoves.Get(i).Col() == maze.NumberCols() - 1) && (possibleMoves.Get(i).Row() == maze.NumberRows() - 1) ) {
                solution = newStack;
                // Before returning true, do I need to clear the queues and such??? To prevent memory leaks?
                return true;
            }

            solutionsToTest.Enqueue(newStack);
        }
    }

    return false; // Didn't get to the true statement in the while loop, so there is no solution to this maze.
}

/**
* Generate set of grid locations adjacent to "loc" that are within the maze and not walls
* @param maze the maze that we want to solve
* @param loc grid location that we want to move from
* @return set of valid moves
*/
Set<GridLocation> GenerateValidMoves(const Grid& maze, const GridLocation& loc) {
    GridLocation testLocation;
    Set<GridLocation> validMoves;

    // Testing North
    testLocation = GridLocation(loc.Row(), loc.Col() - 1);
    if (maze.IsWithinGrid(testLocation) && maze[testLocation]) {
        validMoves.Add(testLocation);
    }

    // Testing East
    testLocation = GridLocation(loc.Row() + 1, loc.Col());
    if (maze.IsWithinGrid(testLocation) && maze[testLocation]) {
        validMoves.Add(testLocation);
    }

    // Testing South
    testLocation = GridLocation(loc.Row(), loc.Col() + 1);
    if (maze.IsWithinGrid(testLocation) && maze[testLocation]) {
        validMoves.Add(testLocation);
    }

    // Testing West
    testLocation = GridLocation(loc.Row() - 1, loc.Col());
    if (maze.IsWithinGrid(testLocation) && maze[testLocation]) {
        validMoves.Add(testLocation);
    }

    return validMoves;
}

/**
* Check whether a purported solution is really a solution
* @param maze the maze that we want to solve
* @param path solution to check
* @return true it solves the maze, false it doesn't
*/
bool CheckSolution(const Grid& maze, Stack<GridLocation> path) {
    GridLocation loc;
    GridLocation prevLoc;
    Set<GridLocation> locationsVisited;

    loc = path.Pop();

    // If the first location on the stack isn't the end of the maze, this solution is wrong.
    if ( !((loc.Col() == maze.NumberCols() - 1) && (loc.Row() == maze.NumberRows() - 1)) ) {
        return false;
    }

    // If the bottom right corner is a wall there obviously are no solutions to the maze, so then this solution is wrong by default.
    if (!maze[loc]) {
        return false;
    }

    // Iterating through the solution, checking each move to make sure it's valid. If it ends up on (0,0) successfully then the solution works.
    // If it never hits (0,0) it will exit this loop and then return false at the bottom of the method.
    // If it does something wacky like go diagonally it will return false.
    while ( !(path.IsEmpty()) ) {
        prevLoc = loc;
        loc = path.Pop();

        // Testing that the move only moved one space. That it didn't leap across the grid or go diagonally or something.
        if (
                (( prevLoc.Col() == loc.Col() ) && ( abs(prevLoc.Row() - loc.Row()) == 1) ) ||   // Move is valid if it only moves up 1 or down 1
                (( prevLoc.Row() == loc.Row() ) && ( abs(prevLoc.Col() - loc.Col()) == 1) )      // Move is valid if it only moves left 1 or right 1
            ) {
            if (locationsVisited.Contains(loc)) { // Solution went backwards or made a loop or sat in one spot.
                return false;
            }
            locationsVisited.Add(loc); // Move was valid!
            if ( (loc.Col() == 0) && (loc.Row() == 0) ) {
                return true;
            }
        } else { // Move did something odd, return false.
            return false;
        }
    }

    return false;
}
