#pragma once

#include "common.h"
#include "coordinates.h"

class Minefield
{
public:
    CoordinatesToFieldsMapping& getCoordinatesToFieldsMapping() { return coordinatesToFieldsMapping_; }
    void addField(const std::shared_ptr<Field>& field);
    std::shared_ptr<Field> operator[](Coordinates coordinates) const;

    [[nodiscard]] CoordinatesToFieldsMapping::const_iterator begin() const { return coordinatesToFieldsMapping_.begin(); }
    [[nodiscard]] CoordinatesToFieldsMapping::const_iterator end() const { return coordinatesToFieldsMapping_.end(); }

private:
    CoordinatesToFieldsMapping coordinatesToFieldsMapping_;
};