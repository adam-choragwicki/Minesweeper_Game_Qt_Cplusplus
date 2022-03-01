#include "fields_manager.h"
#include "field.h"

#include <memory>

// TODO test if given number of fields are created and non-empty
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

// TODO test if all fields are empty
void FieldManager::destroyFields(Minefield& minefield)
{
    minefield.clear();
}

// TODO test if mine counts assigned to each field are correct
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

// TODO test if returned vector consists of adjacent fields
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

// TODO test if returned integer is correct
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

// TODO test if returned vector consists of correct adjacent fields coordinates
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
