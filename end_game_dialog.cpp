#include "end_game_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>
#include <QDebug>

EndGameDialog::EndGameDialog(bool win)
{
    QMessageBox* pMessageBox;

    if(win == true)
    {
        pMessageBox = new QMessageBox(QMessageBox::Icon::Warning, "Congratulations", "You win");
    }
    else
    {
        pMessageBox = new QMessageBox(QMessageBox::Icon::Warning, "BOOM", "Oops");
    }

    QPushButton* p_RestartButton = new QPushButton("Restart", pMessageBox);
    QPushButton* p_CloseButton = new QPushButton("Close", pMessageBox);

    pMessageBox->addButton(p_RestartButton, QMessageBox::NoRole);
    pMessageBox->addButton(p_CloseButton, QMessageBox::NoRole);

    int userInput = pMessageBox->exec();

    enum BUTTON_MEANINGS
    {
        RESTART = 0,
        CLOSE = 1
    };

    qDebug() << "User input: " << userInput;

    if(userInput == RESTART)
    {
        QCoreApplication::exit(1);
    }
    else if(userInput == CLOSE)
    {
        exit(0);
    }
    else
    {
        assert(false);
    }

    delete pMessageBox;
}
