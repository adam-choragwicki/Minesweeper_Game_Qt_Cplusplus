#pragma once

#include <QMainWindow>
#include "QGridLayout"
#include "mine_field_button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(int rowCount, int columnCount, QWidget* parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    const int ROW_COUNT;
    const int COLUMN_COUNT;
    const int BUTTON_SIZE = 100;

    QVector<MineFieldButton*> mineFieldButtons;

    QGridLayout* m_MainGridLayout;
};
