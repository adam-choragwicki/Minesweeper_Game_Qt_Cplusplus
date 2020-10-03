#pragma once

#include <QPushButton>
#include <QMouseEvent>

class MineFieldButton : public QPushButton
{
public:
    MineFieldButton(int x, int y, int fieldNumber, QString text = "");
    int GetX() const {return X;}
    int GetY() const {return Y;}
    int GetFieldNumber() const {return FIELD_NUMBER;}
    bool IsMine() {return m_IsMine;}
    void SetMine() {m_IsMine = true;}
    void SetAdjacentMineCount(int adjacentMineCount) {m_AdjacentMineCount = adjacentMineCount;}

private:
    const int SIZE = 30;
    const int FONT_SIZE = 20;
    const int X;
    const int Y;
    const int FIELD_NUMBER;
    const QString TEXT_COLOR = "color: black";

    bool m_IsMine;
    int m_AdjacentMineCount;

    void TestMineField();
    void MarkMine();

    virtual void mousePressEvent(QMouseEvent* event) override;
};
