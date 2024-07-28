//------------------------------------------------------------------------------
//-----handling of rows and columns in on dataset-------------------------------
//------------------------------------------------------------------------------

#include "rowcolumn.h"

//constructors
RowColumn::RowColumn(int row, int column) :
    row(row), column(column){
};

RowColumn::RowColumn(MovementDirection rowMovement, MovementDirection columnMovement) :
    RowColumn((int)rowMovement, (int)columnMovement) {
};

RowColumn::RowColumn(const RowColumn& other) :
    row(other.row), column(other.column){
}

//operators
RowColumn& RowColumn::operator=(const RowColumn& other) { 
    this->row = other.row;
    this->column = other.column;
    return *this;
}

RowColumn& RowColumn::operator+(const RowColumn& other) {
    this->row += other.row;
    this->column += other.column;
    return *this;
}

RowColumn& RowColumn::operator+=(const RowColumn& other) {
    return RowColumn::operator+(other);
}

RowColumn& RowColumn::operator-(const RowColumn& other) {
    this->row -= other.row;
    this->column -= other.column;
    return *this;
}

RowColumn& RowColumn::operator-=(const RowColumn& other) {
    return RowColumn::operator-(other);
}

bool RowColumn::operator==(const RowColumn &other) {
    return ((row == other.row) && (column == other.column));

}

std::ostream& operator<<(std::ostream& os, const RowColumn& rowColumn) {
    os << "Row: " << rowColumn.row << ", Column: " << rowColumn.column;
    return os;
}
