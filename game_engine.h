#pragma once

#include "coordinates.h"
#include "field.h"

#include <QVector>

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(int rowCount, int columnCount, int minePercentage, QMap<Coordinates, Field*>& mineFieldButtons);
    void debugUncoverAll();
    void processLeftClick(Field* field);
    void processRightClick(Field* field);
    void restartGame();

signals:
    void gameEnd(GameResult gameResult);

private:
    void assignAdjacentMinesCountToAllFields() const;
    int countFieldsWithoutMine();
    QVector<Coordinates> calculateAdjacentFieldsCoordinates(const Coordinates& coordinates) const;
    QVector<Field*> getAdjacentFields(const Coordinates& coordinates) const;
    void generateMines() const;
    void processGameEnd(GameResult gameResult);
    void resetFields();
    void uncoverAdjacentEmptyFields(Field* field);
    void uncoverRecursively(Field* field);

    QMap<Coordinates, Field*>& mineFieldButtons_;
    const int rowCount_;
    const int columnCount_;
    const int minePercentage_;
};
