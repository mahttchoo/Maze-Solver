# lab4-maze-finder-f21

Your job in this assignment is to find a route through a maze, starting at the upper left corner of the maze, and ending at the lower right corner.  When you get your code working, you will be able to visualize the work your code does to  find the route.


## Step 1: Implement Stack, Queue, and Set

The maze finding algorithm uses a stack, a queue, and a set.  You should start by implementing each of these ADT's.  Add code to the following files:

- `Stack.h` - this file contains a template class declaration for a _Stack ADT_ with the following public methods:  _Push_, _Peek_, _Pop_, _IsEmpty_, and _Size_.  Implement these methods  using the private member _ _list_ to store the values on the stack.  As we discussed in class, to get _O(1)_ time complexity for _Stack_ operations, new values should be appended to the end of the list. 

- `Queue.h` - this file contains a template class declaration for a _Queue ADT_ with the following public methods:  _Enqueue_, _Dequeue_, _IsEmpty_, and _Size_.  Implement them using the private member _ _list_ to store the items in the queue.  Enqueue new items at the start of the list, and dequeue them from the end of the list.  This is not an optimal implementation because the time complexity of Enqueue will be _O(N)_, but it saves work implementing it this way.  Once you get the maze solver fully working, you will have the extra credit option of reimplementing the queue using a circular array.

- `Set.h` - this file contains a template class declaration for a _Set ADT_ with the following public methods:  _Add_, _Contains_, _Get_, and _Size_.  You will not need to implement any of the other methods that would usually be found in a _Set ADT_ because they are not needed for this algorithm.  Implement them using the private member _ _list_ to store the items in the queue.  Keep in mind that if the set already contains a certain element, it is not an error to try to add it again to the set, but the element will not actually be added a second time.  (Remember that the List ADT has a method for you to find out whether the item is present.) The purpose of the _Get_ method is so you can iterate through the elements of the set as illustrated in this friend function:

```
    friend ostream& operator<<(ostream& os, const Set& set) {
        os << '{';
        for (size_t i = 0; i < set.Size(); i ++ ) {
            if (i > 0) {
                os << ", ";
            }
            os << set.Get(i);
        }
        os << '}';
    }
```

When you have finished implementing these methods, you can compile and run the main program.  It contains some simple validation code that will make sure your Stack, Queue, and Set classes are working properly.


## Step 2:  Understand how our maze will be represented

A maze can be thought of as a two-dimensional array where each element is either a corridor or a wall. In our programming model, a _true_ value will represent a corridor and a _false_ value represents a wall.  

Consider the 5x7 maze pictured below where light gray represents a corridor, and black represents a wall.

![image](https://user-images.githubusercontent.com/58283777/138574967-13fbe9b7-ab03-4868-acaf-22323cae27de.png)

Its two dimensional array representation would be:

![image](https://user-images.githubusercontent.com/58283777/138965299-97859ca5-2337-4ec2-a810-07aceccd0c71.png)

There are two classes that have been implemented for you which you will use:

- _GridLocation_ this class is used to specify a particular location on the grid.  The class stores the specific row number and column number of the location.

- _Grid_  this class is used to represent the grid itself.  Internally it is implemented using a two-dimensional array of bool values, but a programmer determines whether a particular grid location is a corrior or a wall, but indexing with a _GridLocation_ object representing the location you are interested in. 

For instance, if you wanted to find whether the location on the 2nd row and the 3rd column was corridor, you could find that out using the following code:

```
GridLocation loc(2,3);
if ( maze[loc] ) {
	cout << "Corridor" << endl;
}
else {
	cout << "Wall" << endl;
}
```

The _Grid_ class has a useful method called  _IsWithinGrid_ that you will use to determine whether a particular _GridLocation_ is actually within the grid boundaries.  

When you specify a maze file for the program to solve, the main program calls _grid.LoadFromFile_ method to read the maze information into the _grid_.


## Step 3:  Understand how a path through the maze will be represented

A path through the maze is a sequence of grid locations that connect to each other.  We will store the sequence in a _Stack<GridLocation>_.  When we want extend the path to reach the next grid location, we will push the new _GridLocation_ on to the path.

## Step 4:  Write the _GenerateValidMoves_ function

In the file `Maze.cpp`, you should implement the function
  
  `Set<GridLocation> GenerateValidMoves(const Grid& maze, const GridLocation& loc)`  

Given a grid location, there are always four adjacent grid locations to consider: north, east, south, and west.  But some of these grid locations may be
invalid moves because the location is outside the grid or there is a wall at that location.

This function returns the _set_ of grid locations adjacent to _loc_ which are 1) within the maze, and 2) are not walls.  To implement, declare a local variable of type _Set<GridLocation>_ and then _Add_ to it all the grid locations that are within in the maze and not walls.  You should return the _set_ you've just created.


## Step 5:  Write the _SolveMaze_ function

In the file `Maze.cpp`, you should implement the function 
  
  `bool SolveMaze(const Grid& maze, Stack<GridLocation>& solution, CursesWindow* pwindow)`.  
  
This function tries to find a solution to the maze.  If it finds one, it will return _true_ and the solution comes back to the caller via the reference parameter _solution_. If no solution is found, it will return _false_.  The parameter _pwindow_ is used for displaying the paths as your algorithm considers them as possibilities.

Your function will initialize a _queue_ of partial paths to drive its work.  Because the queue stores paths, its type will be `Queue<Stack<GridLocation>>`.  Your function will loop, removing one path from the queue on each iteration.  It will try to extend that path by one additional square.  There may be no way to extend the path further, or multiple ways.  Any path extensions that it does find will be put back on the queue to be considered on another iteration.  In this way, if a path to the ending point exists, it will eventually be found.  In computer science the name _breadth first search_ is given to the type of algorithm that is being used here.

In order to avoid revisiting grid locations that you've considered before you, will also keep track of the _set_ of grid locations  that you have already visited.  When you try to extend a path, if the move is to a  _GridLocation_ that is in this set, then you should not try to extend the path in that direction because you have already found another path that reached that location.  

Here's a sketch of how the algorithm works:
```
1. If the upper left square is a wall, return _false_.
2. Initialize the queue to the path of length 1 that contains the upper left square.
3. Initialize the set of grid locations that you have reached (visited) to contain just the upper left grid location.
4. Loop until the queue is empty
  a.  Dequeue a path
  b.  Add this code to display the path momentarily when program is run with -visualize flag:
        if (pwindow) {
            pwindow->ShowPath(path, false);
        }
	c.  Generate set of the valid moves from the _GridLocation_ at the end of the path (i.e. the top item of the stack)
	d.  For each valid move in this set which is not in the set of visited grid locations
		  i.  Generate a new path which consists of the path under consideration plus a move to this grid location
		  ii. If the end of this path is the lower left corner, return true, this path is your solution
		  iii. Otherwise put your new path back on the queue so it can be extended further
	    	  iv. Mark this grid location as visited by adding it the set of visited grid locations
5. If you end up here, you didn't find a solution, so you better return false
```

## Step 6:  Write the _CheckSolution_ function

In the file `Maze.cpp`, you should implement the function
  
  `bool CheckSolution(const Grid& maze, Stack<GridLocation> path)`.  
  
The main program uses this function  to determine whether a path is actually a solution to the maze.  
  
Here are the things you need to verify:
- The path must start at the entry (upper left corner) of the maze
- The path must end at the exit (lower right corner) of the maze
- Each location in the path is a valid move from the previous location in the path
- The path must not contain a loop, i.e. the same location cannot appear more than once in the path

Here's a sketch of an algorithm you can use:

```
Loop until the path is empty
1. Remove the next grid location from the path
2. If the grid location is outside the grid or a wall, return false
3. If this is the first iteration of the loop return false if the grid location isn't the lower right corner
4. If this is not the first iteration, return false if the grid location from the previous iteration of the loop
       is not one of the valid moves from the current grid location
```

## Step 7: Make sure it works

Make sure your code compiles and passes the validation tests for your _Stack_, _Queue_, and _Set_ implementations.

Then make sure that it works with each of the provided maze files.  Mazes with solutions are located in the `solvable` subdirectory, and mazes with no solution are located in the `unsolvable` directory.

To run your program with the 2x2 solvable maze, run your program like this:

`./MazeSolver ../solvable/2x2.maze`

Or to run your pogram with the 2x2 unsolvable maze, run your program like this:

`./MazeSolver ../unsolvable/2x2.maze`

If you want to use the debugger to find a problem with your code, you should edit your run configuration to specify the working directory and program arguments as shown below:

![image](https://user-images.githubusercontent.com/58283777/138576234-4770ade3-e168-4bbf-bc9d-9780af808110.png)

![image](https://user-images.githubusercontent.com/58283777/138576255-705adf8c-f46e-4557-8a92-fcad9c0dc46f.png)
	
Make sure you run it with `valgrind --leak-check=full` to make sure it does not report any memory problems.


## Step 8: Visualizing the algorithm at work

To see the animation of your code at work, specify the `-visualize` flag on the command line.  For example,

`./MazeSolver -visualize ../solvable/17x37.maze`
 
Then sit back and enjoy.  When the animation is done, press the space bar to end the program.ls


## Extra Credit Options

Only consider doing these after you have got the full assignment working

1)  Queue class: implement the list using a circular array instead of using VariableArrayList
2)  Set class:  keep the list in sorted order, and use binary search to determine if the item is in the set


