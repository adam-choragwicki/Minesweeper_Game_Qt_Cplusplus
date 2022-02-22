#pragma once

#include <array>

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
    int rowCount;
    int columnCount;
    int minePercentage;
};

namespace gameParametersLimits
{
    const int minRowCount = 10;
    const int maxRowCount = 30;
    const int minColumnCount = 10;
    const int maxColumnCount = 30;

    const std::array<int, 3> minePercentageOptions{10, 20, 30};
}
