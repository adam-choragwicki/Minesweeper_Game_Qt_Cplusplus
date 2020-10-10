#include "game_dimensions_dialog_window.h"
#include "game_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    GameDimensionsDialogWindow gameDimensionsDialogWindow;

    while(true)
    {
        if(gameDimensionsDialogWindow.exec() != -1)
        {
            break;
        }
    }

    while(true)
    {
        GameWindow gameWindow(gameDimensionsDialogWindow.GetRowCount(), gameDimensionsDialogWindow.GetColumnCount());
        gameWindow.show();

        switch(application.exec())
        {
        case 0:
            exit(0);
            break;
        case 1:
            continue;
            break;
        }
    }

    return 0;
}
