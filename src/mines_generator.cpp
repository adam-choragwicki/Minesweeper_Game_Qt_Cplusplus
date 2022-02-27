#include "mines_generator.h"
#include "coordinates.h"
#include "field.h"

#include <QRandomGenerator>
#include <QSet>
#include <QDebug>

// TODO test how many mines were generated
void MineGenerator::generateMines(const GameParameters& gameParameters, const Minefield& minefield) const
{
    const int targetMineCount = static_cast<int>(gameParameters.rowCount * gameParameters.columnCount * (double(gameParameters.minePercentage) / 100));

    qDebug() << "Target mine count: " << targetMineCount;

    QRandomGenerator* randomGenerator = QRandomGenerator::global();

    QSet<QPair<int, int>> mineCoordinatesSet;

    while(mineCoordinatesSet.size() != targetMineCount)
    {
        mineCoordinatesSet.insert(QPair<int, int>(randomGenerator->bounded(1, gameParameters.rowCount), randomGenerator->bounded(1, gameParameters.columnCount)));
    }

    qDebug() << "Generated " << mineCoordinatesSet.size() << " mines";

    for(auto& mineCoordinates : mineCoordinatesSet)
    {
        minefield[Coordinates(mineCoordinates.first, mineCoordinates.second)]->setMine();
    }
}
