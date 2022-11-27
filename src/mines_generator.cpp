#include "mines_generator.h"
#include "field.h"

#include <QRandomGenerator>
#include <set>

void MineGenerator::generateMines(const MinefieldParameters& gameParameters, const Minefield& minefield)
{
    const int targetMineCount = static_cast<int>(gameParameters.rowCount * gameParameters.columnCount * (double(gameParameters.minePercentage) / 100));

    QRandomGenerator* randomGenerator = QRandomGenerator::global();

    std::set<Coordinates> mineCoordinatesSet;

    while(mineCoordinatesSet.size() != targetMineCount)
    {
        mineCoordinatesSet.insert(Coordinates(randomGenerator->bounded(1, gameParameters.rowCount), randomGenerator->bounded(1, gameParameters.columnCount)));
    }

    for(const Coordinates& mineCoordinates : mineCoordinatesSet)
    {
        if(minefield.getCoordinatesToFieldsMapping().contains(mineCoordinates))
        {
            Field* field = minefield.getCoordinatesToFieldsMapping().at(mineCoordinates).get();
            field->placeMine();
        }
        else
        {
            throw std::runtime_error("Cannot place mine on non-existing field.");
        }
    }
}
