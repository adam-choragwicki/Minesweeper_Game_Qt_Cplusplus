#pragma once

#include <map>
#include <memory>

class Coordinates;

class Field;

using CoordinatesToFieldsMapping = std::map<Coordinates, std::unique_ptr<Field>>;

enum class GameResult
{
    win, lose
};

enum class ClickType
{
    left, right
};

struct MinefieldParameters
{
    MinefieldParameters() = default;

    MinefieldParameters(int rowCount, int columnCount, int minePercentage) : rowCount(rowCount), columnCount(columnCount), minePercentage(minePercentage)
    {

    }

    int rowCount {};
    int columnCount {};
    int minePercentage {};
};

namespace GameParametersLimits
{
    const int minRowCount = 10;
    const int maxRowCount = 30;
    const int minColumnCount = 10;
    const int maxColumnCount = 30;

    const std::array<int, 3> minePercentageOptions{10, 20, 30};
}
