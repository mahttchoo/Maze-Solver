//
// Maze solver main program
// Author: Max Benson
// Date: 08/16/2021
//
#include <string.h>
#include <iostream>

#include <fstream>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;

#include "Grid.h"
#include "Stack.h"
#include "Queue.h"
#include "Set.h"
#include "CursesWindow.h"
#include "Maze.h"

void ValidateADTs();

int main(int argc, char* argv[]) {
    Grid maze;
    Stack<GridLocation> solution;
    CursesWindow window;
    ifstream ifs;
    string filename;
    bool fVisualize;

    // Process arguments
    if (argc == 1) {
        ValidateADTs();
        exit(0);
    }
    else if (argc == 2) {
        filename = argv[1];
        fVisualize = false;
    }
    else if (argc != 3 || strcmp(argv[1],"-visualize") != 0) {
        cerr << "Usage: MazeSolver [-visualize] <filename>" << endl;
        exit(1);
    }
    else {
        filename = argv[2];
        fVisualize = true;
        window.InitGraphics();
    }

    // Load maze file
    ifs.open(filename, ifstream::in);
    if (!ifs.good()) {
        cerr << "Can't open '" << filename << "'" << endl;
        exit(2);
    }
    if (!maze.LoadFromFile(ifs)) {
        cerr << "Load from '" << filename << "' failed " << endl;
        exit(3);
    }

    // Display maze and solve
    if (fVisualize) {
        window.ShowGrid(maze);
        if (SolveMaze(maze, solution, &window)){
            window.ShowPath(solution, true);
        }
        getch();
    }
    else {
        cerr << "Maze:" << endl;
        cerr << maze;
        if (SolveMaze(maze, solution)) {
            cerr << "Solution:" << endl;
            cout << solution << endl;
            if (CheckSolution(maze, solution)) {
                cerr << "Solution is correct" << endl;
            } else {
                cerr << "Solution is not correct" << endl;
            }
        } else {
            cerr << "Couldn't find solution to maze." << endl;
        }
    }
    ifs.close();
    return 0;
}

int SumSetElements(const Set<int>& set) {
    int total = 0;
    for (size_t i = 0; i < set.Size(); i++) {
        total += set.Get(i);
    }
    return total;
}

void ValidateADTs() {
    Stack<int> stack;
    Queue<int> queue;
    Set<int> set;

    // Validate Stack ADT
    assert(stack.IsEmpty());
    assert(stack.Size() == 0);

    assert(stack.Push(100));
    assert(stack.Peek() == 100);
    assert(!stack.IsEmpty());
    assert(stack.Size() == 1);

    assert(stack.Push(200));
    assert(stack.Peek() == 200);
    assert(!stack.IsEmpty());
    assert(stack.Size() == 2);

    assert(stack.Pop() == 200);
    assert(stack.Peek() == 100);
    assert(!stack.IsEmpty());
    assert(stack.Size() == 1);

    assert(stack.Pop() == 100);
    assert(stack.IsEmpty());
    assert(stack.Size() == 0);
    cout << "Stack passes validation" << endl;

    // Validate Queue ADT
    assert(queue.IsEmpty());
    assert(queue.Size() == 0);

    assert(queue.Enqueue(100));
    assert(!queue.IsEmpty());
    assert(queue.Size() == 1);

    assert(queue.Enqueue(200));
    assert(!queue.IsEmpty());
    assert(queue.Size() == 2);

    assert(queue.Dequeue() == 100);
    assert(!queue.IsEmpty());
    assert(queue.Size() == 1);

    assert(queue.Dequeue() == 200);
    assert(queue.IsEmpty());
    assert(queue.Size() == 0);
    cout << "Queue passes validation" << endl;

    // Validate Set ADT
    assert(set.Size() == 0);
    assert(!set.Contains(100));

    assert(set.Add(100));
    assert(set.Size() == 1);
    assert(set.Get(0) == 100);
    assert(set.Contains(100));

    assert(set.Add(200));
    assert(set.Size() == 2);
    assert(set.Contains(100));
    assert(set.Contains(200));
    assert(SumSetElements(set) == 300);

    assert(set.Add(150));
    assert(set.Size() == 3);
    assert(set.Contains(100));
    assert(set.Contains(150));
    assert(set.Contains(200));
    assert(SumSetElements(set) == 450);

    assert(set.Add(50));
    assert(set.Size() == 4);
    assert(set.Contains(50));
    assert(set.Contains(100));
    assert(set.Contains(150));
    assert(set.Contains(200));
    assert(SumSetElements(set) == 500);

    assert(set.Add(100));
    assert(set.Size() == 4);

    cout << "Set passes validation" << endl;
}

