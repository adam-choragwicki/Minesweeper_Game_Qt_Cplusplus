#include "minefield.h"
#include "field.h"

void Minefield::addField(const std::shared_ptr<Field> &field)
{
    coordinatesToFieldsMapping_.insert(field->getCoordinates(), field);
}

std::shared_ptr<Field> Minefield::operator[](Coordinates coordinates) const
{
    if(coordinatesToFieldsMapping_.contains(coordinates))
    {
        return coordinatesToFieldsMapping_[coordinates];
    }
    else
    {
        return nullptr;
    }
}

void Minefield::clear()
{
    coordinatesToFieldsMapping_.clear();
}
