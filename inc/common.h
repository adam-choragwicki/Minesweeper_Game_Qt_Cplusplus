#pragma once

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

namespace gameParameters {
const int minRowCount = 10;
const int maxRowCount = 30;
const int minColumnCount = 10;
const int maxColumnCount = 30;
}
