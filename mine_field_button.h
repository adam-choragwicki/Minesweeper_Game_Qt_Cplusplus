#pragma once

#include <QPushButton>
#include <QMouseEvent>

class MineFieldButton : public QPushButton//, QMouseEvent
{
public:
    MineFieldButton(int x, int y, int fieldNumber, QString text = "");
    int GetX() const {return m_X;}
    int GetY() const {return m_Y;}
    int GetFieldNumber() const {return m_FieldNumber;}
    bool IsMine() {return m_IsMine;}
    void SetMine() {m_IsMine = true;}
    void SetAdjacentMineCount(int adjacentMineCount) {m_AdjacentMineCount = adjacentMineCount;}

private:
    const int m_X;
    const int m_Y;
    const int m_FieldNumber;
    const QString m_TextColor = "color: black";
    bool m_IsMine;
    int m_AdjacentMineCount;

    virtual void mousePressEvent(QMouseEvent* ) override;
};
