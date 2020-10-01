#include "game_window.h"
#include "ui_game_window.h"
#include <QDebug>

GameWindow::GameWindow(int rowCount, int columnCount, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    qDebug() << "Received numbers are " << rowCount << ", " << columnCount;
}

GameWindow::~GameWindow()
{
    delete ui;
}

