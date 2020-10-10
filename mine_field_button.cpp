#include "mine_field_button.h"
#include "end_game_dialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>

MineFieldButton::MineFieldButton(int x, int y, QString textString) :
    QPushButton(textString),
    COORDINATES(x, y),
    m_Mine(false),
    m_AlreadyScanned(false),
    m_Flagged(false),
    m_AdjacentMineCount(0)
{
    setFixedSize(SIZE, SIZE);
    setStyleSheet(TEXT_DEFAULT_COLOR);

    QFont currentFont = font();
    currentFont.setPointSize(FONT_SIZE);
    currentFont.setBold(true);
    setFont(currentFont);
}

void MineFieldButton::TestMineField()
{
    if(m_Mine == true)
    {
        setStyleSheet("color: red");
        setText("M");

        qDebug() << "GAME OVER";

        EndGameDialog(false);
    }
    else
    {
        setText(QString::number(m_AdjacentMineCount));
    }

    m_AlreadyScanned = true;
}

void MineFieldButton::LeftClickAction()
{
    if(!m_AlreadyScanned)
    {
        if(!m_Flagged)
        {
            TestMineField();
            emit FieldClicked();
        }
    }
    else
    {
        qDebug() << "CLICK IGNORED";
    }
}

void MineFieldButton::RightClickAction()
{
    if(!m_AlreadyScanned)
    {
        if(m_Flagged == true)
        {
            setText("");
            m_Flagged = false;
        }
        else
        {
            setText("X");
            m_Flagged = true;
        }
    }
}

void MineFieldButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        qDebug() << "LEFT CLICK";
        LeftClickAction();
    }
    else if(event->button() == Qt::MouseButton::RightButton)
    {
        qDebug() << "RIGHT CLICK";
        RightClickAction();
    }
}
