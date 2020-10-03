#pragma once

#include <QPushButton>
#include <QMouseEvent>

class MineFieldButton : public QPushButton
{
    Q_OBJECT
public:
    typedef QPair<int, int> Coordinates;

    MineFieldButton(int x, int y, QString text = "");
    QPair<int, int> GetCoordinates() const {return COORDINATES;}
    bool IsMine() {return m_Mine;}
    void SetMine() {m_Mine = true;}
    void SetAdjacentMineCount(int adjacentMineCount) {m_AdjacentMineCount = adjacentMineCount;}
    bool IsAlreadyScanned() const {return m_AlreadyScanned;}

signals:
    void FieldClicked();

private:
    const int SIZE = 30;
    const int FONT_SIZE = 20;
    const QPair<int, int> COORDINATES;
    const QString TEXT_DEFAULT_COLOR = "color: black";

    bool m_Mine;
    bool m_AlreadyScanned;
    bool m_Flagged;
    int m_AdjacentMineCount;

    void TestMineField();
    void LeftClickAction();
    void RightClickAction();

    virtual void mousePressEvent(QMouseEvent* event) override;
};
