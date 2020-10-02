#pragma once

#include <QPushButton>
#include <QMouseEvent>

class MineFieldButton : public QPushButton
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
    const QString TEXT_COLOR = "color: black";
    const int POINT_SIZE = 20;
    bool m_IsMine;
    int m_AdjacentMineCount;

    void TestMineField();
    void MarkMine();

    virtual void mousePressEvent(QMouseEvent* event) override;
};
