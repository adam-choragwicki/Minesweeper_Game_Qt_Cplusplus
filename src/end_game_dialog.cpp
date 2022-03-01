#include "end_game_dialog.h"

#include <QPushButton>
#include <QApplication>

EndGameDialog::EndGameDialog(QWidget* parent, GameResult gameResult) : QMessageBox(parent)
{
    if(gameResult == GameResult::win)
    {
        setIcon(QMessageBox::Icon::Information);
        setWindowTitle("Congratulations");
        setText("You win");
    }
    else if(gameResult == GameResult::lose)
    {
        setIcon(QMessageBox::Icon::Warning);
        setWindowTitle("Game over");
        setText("Oops, do you want to play again?");
    }

    setStyleSheet("color: black");

    addButton(new QPushButton("Restart"), QMessageBox::NoRole);
    addButton(new QPushButton("Close"), QMessageBox::NoRole);

    int userInput = this->exec();

    enum buttonMeanings
    {
        restart = 0,
        close = 1
    };

    if(userInput == restart)
    {
        setResult(QMessageBox::Reset);
    }
    else if(userInput == close)
    {
        setResult(QMessageBox::Close);
    }
}
