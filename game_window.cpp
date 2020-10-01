#include "game_window.h"
#include "ui_game_window.h"
#include <QDebug>

GameWindow::GameWindow(int rowCount, int columnCount, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , ROW_COUNT(rowCount), COLUMN_COUNT(columnCount)
{
    ui->setupUi(this);

    qDebug() << "Received numbers are " << ROW_COUNT << ", " << COLUMN_COUNT;

    m_MainGridLayout = new QGridLayout;
    m_MainGridLayout->setHorizontalSpacing(0);
    m_MainGridLayout->setVerticalSpacing(0);
    m_MainGridLayout->setMargin(0);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    ui->centralwidget->setLayout(m_MainGridLayout);

    for(int x = 1; x <= ROW_COUNT; x++)
    {
        for(int y = 1; y <= COLUMN_COUNT; y++)
        {
            QPushButton* button = new QPushButton(QString::number(x) + "," + QString::number(y));
            button->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
            buttons.push_back(button);

            m_MainGridLayout->addWidget(button, x, y);
        }
    }
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_MainGridLayout;
}
