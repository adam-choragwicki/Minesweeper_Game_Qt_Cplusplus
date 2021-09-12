#include "game_engine.h"

#include <QRandomGenerator>

GameEngine::GameEngine(int rowCount, int columnCount, int minePercentage, QMap<Coordinates, Field *>& mineFieldButtons) :
    mineFieldButtons_(mineFieldButtons),
    rowCount_(rowCount),
    columnCount_(columnCount),
    minePercentage_(minePercentage)
{
    generateMines();
    assignAdjacentMinesCountToAllFields();
}

void GameEngine::generateMines() const
{
    const int targetMineCount = rowCount_ * columnCount_ * (double(minePercentage_) / 100);

    qDebug() << "Target mine count: " << targetMineCount;

    QRandomGenerator* randomGenerator = QRandomGenerator::global();

    QSet<QPair<int, int>> mineCoordinatesSet;

    while(mineCoordinatesSet.size() != targetMineCount)
    {
        mineCoordinatesSet.insert(QPair<int, int>(randomGenerator->bounded(1, rowCount_), randomGenerator->bounded(1, columnCount_)));
    }

    qDebug() << "Generated " << mineCoordinatesSet.size() << " mines";
    assert(targetMineCount == mineCoordinatesSet.size());

    for(auto& mineCoordinates : mineCoordinatesSet)
    {
        mineFieldButtons_[Coordinates(mineCoordinates.first, mineCoordinates.second)]->setMine();
    }
}

void GameEngine::resetFields()
{
    for(auto& field : mineFieldButtons_)
    {
        field->reset();
    }
}

void GameEngine::restartGame()
{
    resetFields();
    generateMines();
    assignAdjacentMinesCountToAllFields();
}

void GameEngine::assignAdjacentMinesCountToAllFields() const
{
    for(auto& mineFieldButton : mineFieldButtons_)
    {
        int adjacentMineCount = 0;

        if(mineFieldButton->isMine())
        {
            /*If a field is mine itself an adjacent mine count is irrelevant*/
            mineFieldButton->setAdjacentMineCount(-1);
            continue;
        }
        else
        {
            Coordinates coordinates = mineFieldButton->getCoordinates();

            Field* otherMineFieldButton = nullptr;

            QVector<Coordinates> adjacentFieldsRelativeCoordinates = calculateAdjacentFieldsCoordinates(coordinates);

            for(auto& coordinates : adjacentFieldsRelativeCoordinates)
            {
                otherMineFieldButton = mineFieldButtons_.value(coordinates, nullptr);

                if(otherMineFieldButton)
                {
                    if(otherMineFieldButton->isMine() == true)
                    {
                        ++adjacentMineCount;
                    }
                }
            }
        }

        mineFieldButton->setAdjacentMineCount(adjacentMineCount);
    }
}

void GameEngine::uncoverAdjacentEmptyFields(Field* field)
{
    uncoverRecursively(field);
}

void GameEngine::uncoverRecursively(Field* field)
{
    if(field->uncover() == 0)
    {
        QVector<Field*> adjacentFields = getAdjacentFields(field->getCoordinates());

        for(auto& field : adjacentFields)
        {
            if(!field->isUncovered())
            {
                uncoverRecursively(field);
            }
        }
    }
    else
    {
        return;
    }
}

QVector<Field*> GameEngine::getAdjacentFields(const Coordinates& coordinates) const
{
    QVector<Coordinates> adjacentFieldsRelativeCoordinates = calculateAdjacentFieldsCoordinates(coordinates);
    QVector<Field*> adjacentFields;

    for(auto& coordinates : adjacentFieldsRelativeCoordinates)
    {
        Field* field = mineFieldButtons_.value(coordinates, nullptr);

        if(field)
        {
            adjacentFields.push_back(field);
        }
    }

    return adjacentFields;
}

QVector<Coordinates> GameEngine::calculateAdjacentFieldsCoordinates(const Coordinates& coordinates) const
{
    const QVector<QPair<int, int>> adjacentFieldsOffsets = {{0, -1},
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

int GameEngine::countFieldsWithoutMine()
{
    int counter = 0;

    for(auto& mineFieldButton : mineFieldButtons_)
    {
        if((!mineFieldButton->isMine()) && !mineFieldButton->isUncovered())
        {
            ++counter;
        }
    }

    return counter;
}

void GameEngine::processGameEnd(GameResult gameResult)
{
    emit gameEnd(gameResult);
}

void GameEngine::processLeftClick(Field* field)
{
    if(!field->isUncovered())
    {
        if(!field->isFlagged())
        {
            if(field->uncover() == -1)
            {
                processGameEnd(GameResult::lose);
            }
            else if(field->uncover() == 0)
            {
                uncoverAdjacentEmptyFields(field);
            }
        }

        int fieldsWithoutMineLeft = countFieldsWithoutMine();

        qDebug() << "Empty fields left: " << fieldsWithoutMineLeft;

        if(fieldsWithoutMineLeft == 0)
        {
            processGameEnd(GameResult::win);
        }
    }
}

void GameEngine::processRightClick(Field* field)
{
    if(!field->isUncovered())
    {
        field->toggleFlag();
    }
}

void GameEngine::debugUncoverAll()
{
    for(auto& mineField : mineFieldButtons_)
    {
        mineField->uncover();
    }
}
