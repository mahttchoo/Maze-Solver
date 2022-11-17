//
// Interface Definition for the Grid Class
// Author: Max Benson
// Date: 08/15/2021
//

#ifndef GRID_H
#define GRID_H

#include <iostream>
using std::ostream;
using std::istream;
using std::string;
using std::endl;

#include "GridLocation.h"

class Grid {
public:
    Grid();
    Grid(int nRows, int nCols);
    Grid(const Grid& other);
    ~Grid();

    const Grid& operator=(const Grid& other);

    int NumberRows() const;
    int NumberCols() const;
    bool IsWithinGrid(const GridLocation& loc) const;

    bool operator[] (const GridLocation& loc) const;
    bool& operator[] (const GridLocation& loc);
    bool LoadFromFile(istream& is);

    friend ostream& operator<<(ostream& os, const Grid& grid) {
        for (size_t row = 0; row < grid._nRows; row ++) {
            for (size_t col = 0; col < grid._nCols; col ++) {
                if (grid._rows[row][col]) {
                    os << '-';
                }
                else {
                    os << '@';
                }
            }
            os << endl;
        }
        return os;
    }

private:
    void Clear();

    bool** _rows;
    int _nRows;
    int _nCols;
};

#endif //GRID_H
