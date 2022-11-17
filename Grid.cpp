//
// Method implementation for the Grid Class
// Author: Max Benson
// Date: 08/15/2021
//

#include "Grid.h"

/**
 * Default constructor
 * Creates an 0x0 grid
 */
Grid::Grid() {
    _rows = nullptr;
    _nRows = 0;
    _nCols = 0;
}

/**
 * Default constructor
 * Creates an empty nRowsxnCols grid
 * @param nRows = number of rows
 * @param nCols = number of columns
 */
Grid::Grid(int nRows, int nCols) {
    _nRows = nRows;
    _nCols = nCols;
    _rows = new bool*[_nRows];
    for (size_t row = 0; row < _nRows; row ++) {
        _rows[row] = new bool[_nCols];
        for (size_t col = 0; col < _nCols; col ++) {
            _rows[row][col] = false;
        }
    }
}

/**
 * Copy Constructor
 * Creates a deep copy of the grid.
 * @param other the grid to be copied
 */
Grid::Grid(const Grid& other) {
   _nRows = other._nRows;
   _nCols = other._nCols;
   _rows = new bool*[_nRows];
    for (size_t row = 0; row < _nRows; row ++) {
        _rows[row] = new bool[_nCols];
        for (size_t col = 0; col < _nCols; col ++) {
            _rows[row][col] = other._rows[row][col];
        }
    }
}

/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
Grid::~Grid() {
    Clear();
}

/**
 * Copy assignment operator
 * Enables deep copy assignment using the operator = overload.
 * Uses the copy constructor to copy the rhs.  Then swaps internals of
 * the copy with this.  By doing it this way, the old contents
 * of this will be automatically freed when the method finishes.
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
const Grid& Grid::operator=(const Grid& rhs) {
    if (this != &rhs) {
        Clear();
        _nRows = rhs._nRows;
        _nCols = rhs._nCols;
        _rows = new bool*[_nRows];
        for (size_t row = 0; row < _nRows; row ++) {
            _rows[row] = new bool[_nCols];
            for (size_t col = 0; col < _nCols; col ++) {
                _rows[row][col] = rhs._rows[row][col];
            }
        }
    }
    return *this;
}

/**
 * Return number of rows in grid
 * @return number of rows
 */
int Grid::NumberRows() const {
    return _nRows;
}

/**
 * Return number of columns in grid
 * @return number of columns
 */
int Grid::NumberCols() const {
    return _nCols;
}


/**
 * Overload [] operator for indexing grid with a GridLocation (for retrieval)
 * @param loc grid location
 * @return true/false stored at that location in grid
 */
bool Grid::operator[] (const GridLocation& loc) const {
    return _rows[loc.Row()][loc.Col()];
}

/**
 * Overload [] operator for indexing grid with a GridLocation (for update)
 * @param loc grid location
 * @return settable location fo that location on the grid
 */
bool& Grid::operator[] (const GridLocation& loc) {
    return _rows[loc.Row()][loc.Col()];
}

/**
 * Determine whether a GridLocaiton is within limits of grid
 * @param loc grid location
 * @return true if within grid, false if not
 */
bool Grid::IsWithinGrid(const GridLocation& loc) const {
    return loc.Row() >= 0 && loc.Row() < _nRows && loc.Col() >= 0 && loc.Col() <= _nCols;
}

/**
 * Load grid with information read from an input file stream
 * @param is file stream to read from
 * @return true if read succesful, false if not
 */
bool Grid::LoadFromFile(istream& is) {
    // Sample Format:
    // 5 7
    // -------
    //-@@@@@-
    //-----@-
    //-@@@-@-
    //-@---@-
    //
    string line;

    // Erase old contents
    Clear();

    // Read from stream
    is >> _nRows;
    is >> _nCols;
    getline(is, line);  // Discard remainder of line number of columns is on
    if (_nRows <= 0 || _nCols <= 0) {
        return false;
    }
    _rows = new bool*[_nRows];
    for (size_t row = 0; row < _nRows; row++) {
        _rows[row] = nullptr;
    }
    for (size_t row = 0; row < _nRows; row++) {
        getline(is, line);
        if (line.length() != _nCols) {
            return false;
        }
        _rows[row] = new bool[_nCols];
        for (size_t col = 0; col < _nCols; col++) {
            if (line[col] == '@') {
                _rows[row][col] = false;
            }
            else if (line[col] == '-') {
                _rows[row][col] = true;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

/**
 * Deallocate allocated memory for grid and reset to be a 0x0 grid
 */
void Grid::Clear() {
    for (size_t row = 0; row < _nRows; row++) {
        delete[] _rows[row];
    }
    delete[] _rows;
    _rows = nullptr;
    _nRows = 0;
    _nCols = 0;
}
