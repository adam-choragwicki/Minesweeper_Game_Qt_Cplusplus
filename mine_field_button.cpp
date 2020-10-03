#include "mine_field_button.h"
#include <QDebug>

MineFieldButton::MineFieldButton(int x, int y, int fieldNumber, QString textString) :
    QPushButton(textString),
    X(x),
    Y(y),
    FIELD_NUMBER(fieldNumber),
    m_IsMine(false),
    m_AdjacentMineCount(0)
{
    setFixedSize(SIZE, SIZE);
    setStyleSheet(TEXT_COLOR);

    QFont currentFont = font();
    currentFont.setPointSize(FONT_SIZE);
    currentFont.setBold(true);
    setFont(currentFont);
}

void MineFieldButton::TestMineField()
{
    if(m_IsMine == true)
    {
        qDebug() << "GAME OVER";
        setText("M");
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
