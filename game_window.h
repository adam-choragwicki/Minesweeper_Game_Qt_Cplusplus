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
    typedef QPair<int, int> Coordinates;

    Ui::GameWindow *ui;
    const int ROW_COUNT;
    const int COLUMN_COUNT;
    const int MINE_FIELD_COUNT = ROW_COUNT * COLUMN_COUNT;
    const double MINE_COVERAGE_PERCENTAGE = 0.2;
    const int BUTTON_SIZE = 100;

    QMap<Coordinates, MineFieldButton*> mineFieldButtons;
    QGridLayout* m_MainGridLayout;

    void GenerateMines(QMap<Coordinates, MineFieldButton*> &mineFieldButtons) const;
    void ScanForMines() const;
};
