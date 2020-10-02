#include "mine_field_button.h"
#include  <QDebug>

MineFieldButton::MineFieldButton(int x, int y, int fieldNumber, QString text) :
    QPushButton(text),
    m_X(x),
    m_Y(y),
    m_FieldNumber(fieldNumber),
    m_IsMine(false),
    m_AdjacentMineCount(0)
{
    setStyleSheet(m_TextColor);
}

void MineFieldButton::mousePressEvent(QMouseEvent* /*event*/)
{
    setText(QString::number(m_AdjacentMineCount));
    qDebug() << "MOUSE PRESSED";
}
