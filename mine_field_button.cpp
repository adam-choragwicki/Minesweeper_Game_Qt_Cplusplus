#include "mine_field_button.h"

MineFieldButton::MineFieldButton(int x, int y, int fieldNumber, QString text) :
    QPushButton(text),
    m_X(x),
    m_Y(y),
    m_FieldNumber(fieldNumber)
{
    setStyleSheet(m_TextColor);
}
