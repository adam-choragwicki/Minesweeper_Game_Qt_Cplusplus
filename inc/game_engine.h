#pragma once

#include "coordinates.h"
#include "field.h"
#include "common.h"

#include <QVector>

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(const GameParameters& gameParameters, QMap<Coordinates, std::shared_ptr<Field>>& mineFieldButtons);

    [[maybe_unused]] void debugUncoverAll();
    void processLeftClick(std::shared_ptr<Field>& field);
    void processRightClick(std::shared_ptr<Field>& field);
    void restartGame();

signals:
    void gameEnd(GameResult gameResult);

private:
    void assignAdjacentMinesCountToAllFields() const;
    int countFieldsWithoutMine();
    [[nodiscard]] QVector<Coordinates> calculateAdjacentFieldsCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] QVector<std::shared_ptr<Field>> getAdjacentFields(const Coordinates& coordinates) const;
    void generateMines() const;
    void processGameEnd(GameResult gameResult);
    void resetFields();
    void uncoverAdjacentEmptyFields(std::shared_ptr<Field>& field);
    void uncoverRecursively(std::shared_ptr<Field>& field);

    const GameParameters gameParameters_;
    QMap<Coordinates, std::shared_ptr<Field>>& mineFieldButtons_;
};
