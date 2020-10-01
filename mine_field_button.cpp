#include "mine_field_button.h"

MineFieldButton::MineFieldButton(int x, int y, QString text) : QPushButton(text)
{
    m_X = x;
    m_Y = y;
}
