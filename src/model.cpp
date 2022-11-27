#include "model.h"
#include "log_manager.h"

Model::Model(const MinefieldParameters& minefieldParameters)
{
    minefield_ = std::make_unique<Minefield>(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, *minefield_);
    FieldsManager::assignAdjacentMinesCountToAllFields(*minefield_);
}

void Model::update(const MinefieldParameters& minefieldParameters)
{
    minefield_ = std::make_unique<Minefield>(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, *minefield_);
    FieldsManager::assignAdjacentMinesCountToAllFields(*minefield_);
}

void Model::processGameEnd(GameResult gameResult)
{
    emit gameEndEvent(gameResult);
}
