#pragma once

#include <QPushButton>

class MineFieldButton : public QPushButton
{
public:
    MineFieldButton(int x, int y, QString text = "");
    int GetX() {return m_X;}
    int GetY() {return m_Y;}

private:
    int m_X;
    int m_Y;
};
