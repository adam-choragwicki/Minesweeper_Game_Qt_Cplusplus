#include "game_engine.h"

GameEngine::GameEngine(const GameParameters& gameParameters) :
        gameParameters_(gameParameters)
{

}

void GameEngine::restartGame()
{
    fieldManager_.destroyFields(minefield_);
    fieldManager_.createFields(gameParameters_, minefield_);

    mineGenerator_.generateMines(gameParameters_, minefield_);

    fieldManager_.assignAdjacentMinesCountToAllFields(minefield_);

    emit updateFrontend();
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
            else
            {
                if(field->uncover() == 0)
                {
                    fieldUncoverer_.uncoverAdjacentEmptyFields(field, minefield_);
                }
            }
        }

        int fieldsWithoutMineLeft = fieldManager_.countCoveredFieldsWithoutMine(minefield_);

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
