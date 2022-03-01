#include "mines_generator.h"
#include "coordinates.h"
#include "field.h"

#include <QRandomGenerator>
#include <QSet>

// TODO test how many mines were generated
void MineGenerator::generateMines(const GameParameters& gameParameters, const Minefield& minefield) const
{
    const int targetMineCount = static_cast<int>(gameParameters.rowCount * gameParameters.columnCount *
                                                 (double(gameParameters.minePercentage) / 100));

    QRandomGenerator* randomGenerator = QRandomGenerator::global();

    QSet<QPair<int, int>> mineCoordinatesSet;

    while(mineCoordinatesSet.size() != targetMineCount)
    {
        mineCoordinatesSet.insert(QPair<int, int>(randomGenerator->bounded(1, gameParameters.rowCount),
                                                  randomGenerator->bounded(1, gameParameters.columnCount)));
    }

    for(auto& mineCoordinates: mineCoordinatesSet)
    {
        auto field = minefield[Coordinates(mineCoordinates.first, mineCoordinates.second)];

        if(field)
        {
            field->placeMine();
        }
        else
        {
            throw std::runtime_error("Cannot place mine on non-existing field.");
        }
    }
}
