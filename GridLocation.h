//
// Interface Definition for the GridLocation Class
// Author: Max Benson
// Date: 08/15/2021
//

#ifndef GRIDLOCATION_H
#define GRIDLOCATION_H

#include <iostream>
using std::ostream;
using std::istream;
using std::string;
using std::endl;

class GridLocation {
public:
    GridLocation();
    GridLocation(int row, int col);

    int Row() const;
    int Col() const;

    friend bool operator <(const GridLocation &lhs, const GridLocation& rhs) {
        return lhs._row < rhs._row || (lhs._row == rhs._row && lhs._col < rhs._col) ;
    }
    friend bool operator >(const GridLocation &lhs, const GridLocation& rhs) {
        return lhs._row > rhs._row || (lhs._row == rhs._row && lhs._col > rhs._col) ;
    }

    friend bool operator==(const GridLocation& lhs, const GridLocation& rhs) {
        return lhs._row == rhs._row && lhs._col == rhs._col;
    }
    friend bool operator!=(const GridLocation& lhs, const GridLocation& rhs) {
        return lhs._row != rhs._row && lhs._col == rhs._col;
    }

    friend ostream& operator<<(ostream& os, const GridLocation& loc) {
        return os << "r" << loc._row << "c" << loc._col;
    }

private:
    int _row;
    int _col;
};


#endif //GRIDLOCATION_H
