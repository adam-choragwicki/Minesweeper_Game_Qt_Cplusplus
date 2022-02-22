#pragma once

#include "coordinates.h"
#include "field.h"

#include <QVector>

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(int rowCount, int columnCount, int minePercentage, QMap<Coordinates, std::shared_ptr<Field>>& mineFieldButtons);

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

    QMap<Coordinates, std::shared_ptr<Field>>& mineFieldButtons_;
    const int rowCount_;
    const int columnCount_;
    const int minePercentage_;
};
