#include "mine_field_button.h"
#include <QDebug>

MineFieldButton::MineFieldButton(int x, int y, int fieldNumber, QString textString) :
    QPushButton(textString),
    m_X(x),
    m_Y(y),
    m_FieldNumber(fieldNumber),
    m_IsMine(false),
    m_AdjacentMineCount(0)
{
    setStyleSheet(TEXT_COLOR);

    QFont currentFont = font();
    currentFont.setPointSize(POINT_SIZE);
    currentFont.setBold(true);
    setFont(currentFont);
}

void MineFieldButton::TestMineField()
{
    if(m_IsMine == true)
    {
        qDebug() << "GAME OVER";
        setText("BOOM");
    }
    else
    {
        setText(QString::number(m_AdjacentMineCount));
    }
}

void MineFieldButton::MarkMine()
{
    if(m_IsMine == true)
    {
        setStyleSheet("color: green");

        qDebug() << "MINE CORRECTLY DETECTED";
        setText("OK");
    }
    else
    {
        setText("X");
    }
}

void MineFieldButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        TestMineField();
    }
    else if(event->button() == Qt::MouseButton::RightButton)
    {
        MarkMine();
    }
}
