#pragma once

#include "coordinates.h"
#include "field.h"
#include "common.h"
#include "minefield.h"
#include "fields_manager.h"
#include "mines_generator.h"
#include "fields_uncoverer.h"

#include <QVector>

class GameEngine : public QObject
{
    Q_OBJECT

signals:
    void gameEndSignal(GameResult gameResult);
    void drawFieldsSignal();
    void connectFieldsProcessingSignal();

public:
    explicit GameEngine(const GameParameters& gameParameters);
    void processLeftClick(std::shared_ptr<Field>& field);
    void processRightClick(std::shared_ptr<Field>& field);
    void restartGame();
    [[nodiscard]] const CoordinatesToFieldsMapping& getCoordinatesToFieldsMapping() const {return minefield_.getCoordinatesToFieldsMapping();}

private:
    void processGameEnd(GameResult gameResult);

    const GameParameters gameParameters_;
    Minefield minefield_;
    FieldManager fieldManager_;
    MineGenerator mineGenerator_;
    FieldUncoverer fieldUncoverer_;
};
