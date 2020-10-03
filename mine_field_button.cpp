#include "mine_field_button.h"
#include <QMessageBox>
#include <QDebug>

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
            /*This case added just for explicity*/
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

        emit FieldClicked();
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
