#pragma once

#include "coordinates.h"
#include "field.h"
#include "common.h"

#include <QVector>

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(const GameParameters& gameParameters, CoordinatesToFieldsMapping& coordinatesToFieldMapping);

    [[maybe_unused]] void debugUncoverAllFields();
    void processLeftClick(std::shared_ptr<Field>& field);
    void processRightClick(std::shared_ptr<Field>& field);
    void restartGame();

signals:
    void gameEnd(GameResult gameResult);

private:
    void assignAdjacentMinesCountToAllFields() const;
    int countCoveredFieldsWithoutMine() const;
    [[nodiscard]] QVector<Coordinates> generateAdjacentFieldsCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] QVector<std::shared_ptr<Field>> getAdjacentFields(const Coordinates& coordinates) const;
    void generateMines() const;
    void processGameEnd(GameResult gameResult);
    void resetFields();
    void uncoverAdjacentEmptyFields(std::shared_ptr<Field>& field);
    void uncoverRecursively(std::shared_ptr<Field>& field);

    const GameParameters gameParameters_;
    CoordinatesToFieldsMapping& coordinatesToFieldsMapping_;
};
