#pragma once

#include "coordinates.h"
#include "field.h"
#include "common.h"
#include "minefield.h"
#include "fields_manager.h"
#include "mines_generator.h"
#include "fields_uncoverer.h"

class Model : public QObject
{
Q_OBJECT

signals:
    void gameEndEvent(GameResult gameResult);

public:
    explicit Model(const MinefieldParameters& minefieldParameters);

    void update(const MinefieldParameters& minefieldParameters);

    [[nodiscard]] const CoordinatesToFieldsMapping& getCoordinatesToFieldsMapping() const
    { return minefield_->getCoordinatesToFieldsMapping(); }

    Minefield* getMinefield() const
    { return minefield_.get(); }

    void processGameEnd(GameResult gameResult);

private:
    std::unique_ptr<Minefield> minefield_;
};
