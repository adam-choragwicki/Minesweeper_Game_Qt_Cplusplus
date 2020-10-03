#pragma once

#include <QPushButton>
#include <QMouseEvent>

class MineFieldButton : public QPushButton
{
public:
    typedef QPair<int, int> Coordinates;

    MineFieldButton(int x, int y, QString text = "");
    QPair<int, int> GetCoordinates() const {return COORDINATES;}
    bool IsMine() {return m_IsMine;}
    void SetMine() {m_IsMine = true;}
    void SetAdjacentMineCount(int adjacentMineCount) {m_AdjacentMineCount = adjacentMineCount;}

private:
    const int SIZE = 30;
    const int FONT_SIZE = 20;
    const QPair<int, int> COORDINATES;
    const QString TEXT_DEFAULT_COLOR = "color: black";

    bool m_IsMine;
    bool m_AlreadyLeftClicked;
    bool m_IsFlagged;
    int m_AdjacentMineCount;

    void TestMineField();
    void RightClickAction();

    virtual void mousePressEvent(QMouseEvent* event) override;
    void LeftClickAction();
};
