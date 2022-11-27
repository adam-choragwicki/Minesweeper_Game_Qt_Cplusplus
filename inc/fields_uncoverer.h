#pragma once

#include "minefield.h"

class FieldsUncoverer
{
public:
    FieldsUncoverer() = delete;

    static void uncoverAdjacentEmptyFields(Field* field, Minefield* minefield);
    [[maybe_unused]] static void debug_UncoverAllFields(const Minefield& minefield);
};
