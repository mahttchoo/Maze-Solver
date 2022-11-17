//
// Method implementation for the GridLocation Class
// Author: Max Benson
// Date: 08/15/2021
//

#include "GridLocation.h"

/**
 * Default constructor
 * Creates an location of (0,0)
 */
GridLocation::GridLocation() {
    _row = 0;
    _col = 0;
}

/**
 * Constructor
 * Creates a specific location
 * @ param row - row number
 * @ param col - column number
 */
GridLocation::GridLocation(int row, int col) {
    _row = row;
    _col = col;
}

/**
 * Returns row number
 * @ return row
 */
int GridLocation::Row() const {
    return _row;
}

/**
 * Returns column number
 * @ return column
 */
int GridLocation::Col() const {
    return _col;
}
