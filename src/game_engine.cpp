#include "game_engine.h"

#include <QRandomGenerator>

GameEngine::GameEngine(const GameParameters& gameParameters, QMap<Coordinates, std::shared_ptr<Field>>& mineFieldButtons) :
        gameParameters_(gameParameters),
        mineFieldButtons_(mineFieldButtons)
{
    generateMines();
    assignAdjacentMinesCountToAllFields();
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
            Coordinates currentFieldCoordinates = mineFieldButton->getCoordinates();

            std::shared_ptr<Field> otherMineFieldButton;

            QVector<Coordinates> allAdjacentFieldsCoordinates = calculateAdjacentFieldsCoordinates(currentFieldCoordinates);

            for(auto& adjacentFieldCoordinates : allAdjacentFieldsCoordinates)
            {
                otherMineFieldButton = mineFieldButtons_.value(adjacentFieldCoordinates, nullptr);

                if(otherMineFieldButton)
                {
                    if(otherMineFieldButton->isMine())
                    {
                        ++adjacentMineCount;
                    }
                }
            }
        }

        mineFieldButton->setAdjacentMineCount(adjacentMineCount);
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
            if(!adjacentField->isUncovered())
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
    QVector<Coordinates> adjacentFieldsCoordinates = calculateAdjacentFieldsCoordinates(coordinates);
    QVector<std::shared_ptr<Field>> adjacentFields;

    for(auto& adjacentFieldCoordinates : adjacentFieldsCoordinates)
    {
        std::shared_ptr<Field> field = mineFieldButtons_.value(adjacentFieldCoordinates, nullptr);

        if(field)
        {
            adjacentFields.push_back(field);
        }
    }

    return adjacentFields;
}

QVector<Coordinates> GameEngine::calculateAdjacentFieldsCoordinates(const Coordinates& coordinates) const
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

void GameEngine::processLeftClick(std::shared_ptr<Field>& field)
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

void GameEngine::processRightClick(std::shared_ptr<Field>& field)
{
    if(!field->isUncovered())
    {
        field->toggleFlag();
    }
}

[[maybe_unused]] void GameEngine::debugUncoverAll()
{
    for(auto& mineField : mineFieldButtons_)
    {
        mineField->uncover();
    }
}
