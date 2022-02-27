#pragma once

#include "minefield.h"

class FieldUncoverer
{
public:
    void uncoverAdjacentEmptyFields(std::shared_ptr<Field>& field, const Minefield& minefield);
    [[maybe_unused]] void debug_UncoverAllFields(const Minefield& minefield);

private:
    void uncoverFieldsRecursively(std::shared_ptr<Field>& field, const Minefield& minefield);
};
