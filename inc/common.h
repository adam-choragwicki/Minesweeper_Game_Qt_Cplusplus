#pragma once

#include <array>
#include <memory>
#include <QMap>

class Coordinates;
class Field;

using CoordinatesToFieldsMapping = QMap<Coordinates, std::shared_ptr<Field>>;

enum class GameResult
{
    win,
    lose
};

enum class ClickType
{
    left,
    right
};

struct GameParameters
{
    GameParameters(int rowCount, int columnCount, int minePercentage) :
    rowCount(rowCount), columnCount(columnCount), minePercentage(minePercentage)
    {

    }

    const int rowCount;
    const int columnCount;
    const int minePercentage;
};

namespace GameParametersLimits
{
    const int minRowCount = 10;
    const int maxRowCount = 30;
    const int minColumnCount = 10;
    const int maxColumnCount = 30;

    const std::array<int, 3> minePercentageOptions{10, 20, 30};
}
