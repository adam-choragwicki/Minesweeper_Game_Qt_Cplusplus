#include "minesweeper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Minesweeper minesweeper;

    return QApplication::exec();
}
