#include "minefield.h"
#include "field.h"
#include "log_manager.h"

Minefield::Minefield(MinefieldParameters minefieldParameters)
{
    for(int row = 1; row <= minefieldParameters.rowCount; ++row)
    {
        for(int column = 1; column <= minefieldParameters.columnCount; ++column)
        {
            const Coordinates coordinates(row, column);
            addField(coordinates);
        }
    }
}

void Minefield::addField(const Coordinates& coordinates)
{
    if(coordinatesToFieldsMapping_.contains(coordinates))
    {
        throw std::runtime_error("Field with given coordinates is already on the minefield. Duplicates are not allowed.");
    }
    else
    {
        coordinatesToFieldsMapping_.insert({coordinates, std::make_unique<Field>(coordinates)});
    }
}

void Minefield::setMine(const Coordinates& coordinates)
{
    Field* field = coordinatesToFieldsMapping_.at(coordinates).get();
    field->setMine();
}
