#include "game_engine.h"

GameEngine::GameEngine(const GameParameters& gameParameters) :
        gameParameters_(gameParameters)
{

}

void GameEngine::restartGame()
{
    fieldManager_.destroyFields(minefield_);
    fieldManager_.createFields(gameParameters_, minefield_);
    emit drawFieldsSignal();

    mineGenerator_.generateMines(gameParameters_, minefield_);

    fieldManager_.assignAdjacentMinesCountToAllFields(minefield_);

    emit connectFieldsProcessingSignal();
}

void GameEngine::processGameEnd(GameResult gameResult)
{
    emit gameEndSignal(gameResult);
}

void GameEngine::processLeftClick(std::shared_ptr<Field>& field)
{
    if(field->isCovered())
    {
        if(!field->isFlagged())
        {
            if(field->uncover() == std::nullopt)
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
