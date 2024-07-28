//------------------------------------------------------------------------------
//-----handling of rows and columns in on dataset-------------------------------
//------------------------------------------------------------------------------

#ifndef ROWCOLUMN_H
#define ROWCOLUMN_H

#include "../../_config/settings.h"
#include <iostream>

struct RowColumn {
    //member variables
    int row;
    int column;

    //constructors
    RowColumn(int row = 0, int column = 0);
    RowColumn(MovementDirection rowMovement, MovementDirection columnMovement);
    RowColumn(const RowColumn& other);

    //operators
    RowColumn& operator=(const RowColumn& other);
    RowColumn& operator+(const RowColumn& other);
    RowColumn& operator+=(const RowColumn& other);
    RowColumn& operator-(const RowColumn& other);
    RowColumn& operator-=(const RowColumn& other);
    bool operator==(const RowColumn& other);

    friend std::ostream& operator<<(std::ostream& os, const RowColumn& rowColumn);

};

#endif // ROWCOLUMN_H
