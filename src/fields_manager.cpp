#include "fields_manager.h"
#include "field.h"

#include <memory>

void FieldManager::createFields(const GameParameters& gameParameters, Minefield& minefield)
{
    for(int x = 1; x <= gameParameters.rowCount; x++)
    {
        for(int y = 1; y <= gameParameters.columnCount; y++)
        {
            std::shared_ptr<Field> field = std::make_shared<Field>(x, y);
            minefield.addField(field);
        }
    }
}

void FieldManager::destroyFields(Minefield& minefield)
{
    minefield.clear();
}

void FieldManager::assignAdjacentMinesCountToAllFields(const Minefield& minefield) const
{
    for(auto& field : minefield)
    {
        int adjacentMineCount = 0;

        if(field->isMine())
        {
            /*If a field is a mine itself an adjacent mine count is irrelevant*/
            field->setAdjacentMineCount(std::nullopt);
            continue;
        }
        else
        {
            Coordinates currentFieldCoordinates = field->getCoordinates();

            QVector<Coordinates> allAdjacentFieldsCoordinates = generateAdjacentFieldsCoordinates(currentFieldCoordinates);

            for(auto& adjacentFieldCoordinates : allAdjacentFieldsCoordinates)
            {
                std::shared_ptr<Field> otherField = minefield[adjacentFieldCoordinates];

                if(otherField && otherField->isMine())
                {
                    ++adjacentMineCount;
                }
            }
        }

        field->setAdjacentMineCount(adjacentMineCount);
    }
}

QVector<std::shared_ptr<Field>> FieldManager::getAdjacentFields(const Coordinates& coordinates, const Minefield& minefield) const
{
    QVector<Coordinates> adjacentFieldsCoordinates = generateAdjacentFieldsCoordinates(coordinates);
    QVector<std::shared_ptr<Field>> adjacentFields;

    for(auto& adjacentFieldCoordinates : adjacentFieldsCoordinates)
    {
        std::shared_ptr<Field> field = minefield[adjacentFieldCoordinates];

        if(field)
        {
            adjacentFields.push_back(field);
        }
    }

    return adjacentFields;
}

int FieldManager::countCoveredFieldsWithoutMine(const Minefield& minefield) const
{
    int counter = 0;

    for(auto& field : minefield)
    {
        if(field->isCovered() && !field->isMine())
        {
            ++counter;
        }
    }

    return counter;
}

QVector<Coordinates> FieldManager::generateAdjacentFieldsCoordinates(const Coordinates& coordinates) const
{
    static const QVector<QPair<int, int>> adjacentFieldsOffsets = {{0, -1},
                                                                   {0, +1},
                                                                   {-1, 0},
                                                                   {+1, 0},
                                                                   {-1, -1},
                                                                   {-1, +1},
                                                                   {+1, -1},
                                                                   {+1, +1}};

    QVector<Coordinates> adjacentFieldsCoordinates;

    for(auto& offsetPair : adjacentFieldsOffsets)
    {
        int adjacentX = coordinates.getRow() + offsetPair.first;
        int adjacentY = coordinates.getColumn() + offsetPair.second;

        if(Coordinates::validateCoordinates(adjacentX, adjacentY))
        {
            adjacentFieldsCoordinates.push_back(Coordinates(adjacentX, adjacentY));
        }
    }

    return adjacentFieldsCoordinates;
}
