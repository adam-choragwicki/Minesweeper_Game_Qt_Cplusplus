#include "fields_uncoverer.h"
#include "field.h"
#include "fields_manager.h"

// TODO test if adjacent empty fields are uncovered
void FieldUncoverer::uncoverAdjacentEmptyFields(std::shared_ptr<Field>& field, const Minefield& minefield)
{
    uncoverFieldsRecursively(field, minefield);
}

// TODO test some kind of scenario of uncovering recursively
void FieldUncoverer::uncoverFieldsRecursively(std::shared_ptr<Field>& field, const Minefield& minefield)
{
    if(field->uncover(true) == 0)
    {
        FieldManager fieldManager;

        QVector<std::shared_ptr<Field>> adjacentFields = fieldManager.getAdjacentFields(field->getCoordinates(), minefield);

        for(auto& adjacentField : adjacentFields)
        {
            if(adjacentField->isCovered())
            {
                uncoverFieldsRecursively(adjacentField, minefield);
            }
        }
    }
    else
    {
        return;
    }
}

// TODO test if all fields are uncovered
[[maybe_unused]] void FieldUncoverer::debug_UncoverAllFields(const Minefield& minefield)
{
    for(auto& field : minefield)
    {
        field->uncover();
    }
}
