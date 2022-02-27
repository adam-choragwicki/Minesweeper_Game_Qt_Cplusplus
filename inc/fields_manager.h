#pragma once

#include "common.h"
#include "minefield.h"

class FieldManager
{
public:
    void createFields(const GameParameters& gameParameters, Minefield& minefield);
    void destroyFields(Minefield& minefield);
    void assignAdjacentMinesCountToAllFields(const Minefield& minefield) const;
    [[nodiscard]] QVector<std::shared_ptr<Field>> getAdjacentFields(const Coordinates& coordinates, const Minefield& minefield) const;
    [[nodiscard]] int countCoveredFieldsWithoutMine(const Minefield& minefield) const;

private:
    [[nodiscard]] QVector<Coordinates> generateAdjacentFieldsCoordinates(const Coordinates& coordinates) const;
};
