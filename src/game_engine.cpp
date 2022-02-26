#include "game_engine.h"

#include <QRandomGenerator>

GameEngine::GameEngine(const GameParameters& gameParameters) :
        gameParameters_(gameParameters)
{
    createFields(gameParameters.rowCount, gameParameters.columnCount);
    generateMines();
    assignAdjacentMinesCountToAllFields();
}

void GameEngine::createFields(int rowCount, int columnCount)
{
    for(int x = 1; x <= rowCount; x++)
    {
        for(int y = 1; y <= columnCount; y++)
        {
            std::shared_ptr<Field> field = std::make_shared<Field>(x, y);
            minefield_.addField(field);
        }
    }
}

void GameEngine::generateMines() const
{
    const int targetMineCount = static_cast<int>(gameParameters_.rowCount * gameParameters_.columnCount * (double(gameParameters_.minePercentage) / 100));

    qDebug() << "Target mine count: " << targetMineCount;

    QRandomGenerator* randomGenerator = QRandomGenerator::global();

    QSet<QPair<int, int>> mineCoordinatesSet;

    while(mineCoordinatesSet.size() != targetMineCount)
    {
        mineCoordinatesSet.insert(QPair<int, int>(randomGenerator->bounded(1, gameParameters_.rowCount), randomGenerator->bounded(1, gameParameters_.columnCount)));
    }

    qDebug() << "Generated " << mineCoordinatesSet.size() << " mines";

    for(auto& mineCoordinates : mineCoordinatesSet)
    {
        minefield_[Coordinates(mineCoordinates.first, mineCoordinates.second)]->setMine();
    }
}

void GameEngine::resetFields()
{
    for(auto& field : minefield_)
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
    for(auto& field : minefield_)
    {
        int adjacentMineCount = 0;

        if(field->isMine())
        {
            /*If a field is a mine itself an adjacent mine count is irrelevant*/
            field->setAdjacentMineCount(-1);
            continue;
        }
        else
        {
            Coordinates currentFieldCoordinates = field->getCoordinates();

            QVector<Coordinates> allAdjacentFieldsCoordinates = generateAdjacentFieldsCoordinates(currentFieldCoordinates);

            for(auto& adjacentFieldCoordinates : allAdjacentFieldsCoordinates)
            {
                std::shared_ptr<Field> otherField = minefield_[adjacentFieldCoordinates];

                if(otherField && otherField->isMine())
                {
                    ++adjacentMineCount;
                }
            }
        }

        field->setAdjacentMineCount(adjacentMineCount);
    }
}

void GameEngine::uncoverAdjacentEmptyFields(std::shared_ptr<Field>& field)
{
    uncoverRecursively(field);
}

void GameEngine::uncoverRecursively(std::shared_ptr<Field>& field)
{
    if(field->uncover() == 0)
    {
        QVector<std::shared_ptr<Field>> adjacentFields = getAdjacentFields(field->getCoordinates());

        for(auto& adjacentField : adjacentFields)
        {
            if(adjacentField->isCovered())
            {
                uncoverRecursively(adjacentField);
            }
        }
    }
    else
    {
        return;
    }
}

QVector<std::shared_ptr<Field>> GameEngine::getAdjacentFields(const Coordinates& coordinates) const
{
    QVector<Coordinates> adjacentFieldsCoordinates = generateAdjacentFieldsCoordinates(coordinates);
    QVector<std::shared_ptr<Field>> adjacentFields;

    for(auto& adjacentFieldCoordinates : adjacentFieldsCoordinates)
    {
        std::shared_ptr<Field> field = minefield_[adjacentFieldCoordinates];

        if(field)
        {
            adjacentFields.push_back(field);
        }
    }

    return adjacentFields;
}

QVector<Coordinates> GameEngine::generateAdjacentFieldsCoordinates(const Coordinates& coordinates) const
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

int GameEngine::countCoveredFieldsWithoutMine() const
{
    int counter = 0;

    for(auto& field : minefield_)
    {
        if(field->isCovered() && !field->isMine())
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

void GameEngine::processLeftClick(std::shared_ptr<Field>& field)
{
    if(field->isCovered())
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

        int fieldsWithoutMineLeft = countCoveredFieldsWithoutMine();

        qDebug() << "Empty fields left: " << fieldsWithoutMineLeft;

        if(fieldsWithoutMineLeft == 0)
        {
            processGameEnd(GameResult::win);
        }
    }
}

void GameEngine::processRightClick(std::shared_ptr<Field>& field)
{
    if(field->isCovered())
    {
        field->toggleFlag();
    }
}

[[maybe_unused]] void GameEngine::debugUncoverAllFields()
{
    for(auto& field : minefield_)
    {
        field->uncover();
    }
}
