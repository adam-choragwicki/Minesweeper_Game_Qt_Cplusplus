#include "game_dimensions_dialog_window.h"
#include "game_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    GameDimensionsDialogWindow gameDimensionsDialogWindow;
    gameDimensionsDialogWindow.exec();

    GameWindow gameWindow(gameDimensionsDialogWindow.getRowCount(), gameDimensionsDialogWindow.getColumnCount(), gameDimensionsDialogWindow.getMinePercentage());

    gameWindow.show();
    application.exec();

    return 0;
}
