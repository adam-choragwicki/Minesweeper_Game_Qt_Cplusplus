#pragma once

#include "coordinates.h"
#include "field.h"
#include "common.h"

#include <QVector>

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(const GameParameters& gameParameters);

    [[maybe_unused]] void debugUncoverAllFields();
    void processLeftClick(std::shared_ptr<Field>& field);
    void processRightClick(std::shared_ptr<Field>& field);
    void restartGame();
    CoordinatesToFieldsMapping& getCoordinatesToFieldsMapping() {return coordinatesToFieldsMapping_;}

signals:
    void gameEnd(GameResult gameResult);

private:
    void assignAdjacentMinesCountToAllFields() const;
    [[nodiscard]] int countCoveredFieldsWithoutMine() const;
    [[nodiscard]] QVector<Coordinates> generateAdjacentFieldsCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] QVector<std::shared_ptr<Field>> getAdjacentFields(const Coordinates& coordinates) const;
    void createFields(int rowCount, int columnCount);
    void generateMines() const;
    void processGameEnd(GameResult gameResult);
    void resetFields();
    void uncoverAdjacentEmptyFields(std::shared_ptr<Field>& field);
    void uncoverRecursively(std::shared_ptr<Field>& field);

    const GameParameters gameParameters_;
    CoordinatesToFieldsMapping coordinatesToFieldsMapping_;
};
