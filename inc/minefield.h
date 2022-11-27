#pragma once

#include "common.h"
#include "coordinates.h"

class Minefield
{
public:
    explicit Minefield(MinefieldParameters minefieldParameters);

    [[nodiscard]] const CoordinatesToFieldsMapping& getCoordinatesToFieldsMapping() const { return coordinatesToFieldsMapping_; }

    void setMine(const Coordinates& coordinates);

    [[nodiscard]] CoordinatesToFieldsMapping::const_iterator begin() const { return coordinatesToFieldsMapping_.begin(); }
    [[nodiscard]] CoordinatesToFieldsMapping::const_iterator end() const { return coordinatesToFieldsMapping_.end(); }

private:
    void addField(const Coordinates& coordinates);

    CoordinatesToFieldsMapping coordinatesToFieldsMapping_;
};
