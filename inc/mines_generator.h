#pragma once

#include "common.h"
#include "minefield.h"

class MineGenerator
{
public:
    void generateMines(const GameParameters& gameParameters, const Minefield& minefield) const;
};
