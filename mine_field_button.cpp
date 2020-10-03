#include "mine_field_button.h"
#include <QMessageBox>
#include <QDebug>

MineFieldButton::MineFieldButton(int x, int y, QString textString) :
    QPushButton(textString),
    COORDINATES(x, y),
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
        setText("M");

        qDebug() << "GAME OVER";

        QMessageBox* pMessageBox = new QMessageBox(QMessageBox::Icon::Warning, "BOOM", "Oops");

        QPushButton* p_ContinueButton = new QPushButton("Continue", pMessageBox);
        QPushButton* p_RestartButton = new QPushButton("Restart", pMessageBox);
        QPushButton* p_CloseButton = new QPushButton("Close", pMessageBox);

        pMessageBox->addButton(p_ContinueButton, QMessageBox::NoRole);
        pMessageBox->addButton(p_RestartButton, QMessageBox::NoRole);
        pMessageBox->addButton(p_CloseButton, QMessageBox::NoRole);

        //TODO Restart not supported yet
        p_RestartButton->setEnabled(false);

        int userInput = pMessageBox->exec();

        enum BUTTON_MEANINGS
        {
            CONTINUE = 0,
            RESTART = 1,
            CLOSE = 2
        };

        qDebug() << "User input: " << userInput;

        if(userInput == CONTINUE)
        {
            return;
        }
        else if(userInput == RESTART)
        {
            //RESTART PLACEHOLDER
        }
        else if(userInput == CLOSE)
        {
            exit(0);
        }
        else
        {
            assert(false);
        }
    }
    else
    {
        setText(QString::number(m_AdjacentMineCount));
    }
}

void MineFieldButton::FlagMine()
{
    if(m_IsMine == true)
    {
        setStyleSheet("color: green");
        setText("OK");
        qDebug() << "MINE CORRECTLY DETECTED";
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
        FlagMine();
    }
}
