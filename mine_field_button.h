#pragma once

#include <QPushButton>

class MineFieldButton : public QPushButton
{
public:
    MineFieldButton(int x, int y, int fieldNumber, QString text = "");
    int GetX() const {return m_X;}
    int GetY() const {return m_Y;}
    int GetFieldNumber() const {return m_FieldNumber;}

private:
    const int m_X;
    const int m_Y;
    const int m_FieldNumber;
    const QString m_TextColor = "color: black";
};
