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
    const QString TEXT_COLOR = "color: black";

    bool m_IsMine;
    int m_AdjacentMineCount;

    void TestMineField();
    void FlagMine();

    virtual void mousePressEvent(QMouseEvent* event) override;
};
