#pragma once

#include <iostream>

class Coordinates
{
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

public:
    Coordinates(int row, int column);

    static bool validateCoordinates(int row, int column);

    [[nodiscard]] int getRow() const {return row_;}
    [[nodiscard]] int getColumn() const {return column_;}

private:
    int row_;
    int column_;
};

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
