#include "game_window.h"
#include "ui_game_window.h"
#include <QRandomGenerator>
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

    int fieldNumber = 1;

    for(int x = 1; x <= ROW_COUNT; x++)
    {
        for(int y = 1; y <= COLUMN_COUNT; y++)
        {
            MineFieldButton* mineFieldButton = new MineFieldButton(x, y, fieldNumber, QString::number(x) + "," + QString::number(y));
            mineFieldButton->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
            mineFieldButtons.push_back(mineFieldButton);
            m_MainGridLayout->addWidget(mineFieldButton, x, y);
            ++fieldNumber;
        }
    }

    GenerateMines(mineFieldButtons);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_MainGridLayout;
}

void GameWindow::GenerateMines(QVector<MineFieldButton*>& mineFieldButtons) const
{
    const int targetMineCount = ROW_COUNT * COLUMN_COUNT * MINE_COVERAGE_PERCENTAGE;

    qDebug() << "Target mine count: " << targetMineCount;

    QRandomGenerator* pRandomGenerator = QRandomGenerator::global();

    QSet<int> randomNumbers;

    while(randomNumbers.size() != targetMineCount)
    {
        randomNumbers.insert(pRandomGenerator->bounded(1, MINE_FIELD_COUNT));
    }

    qDebug() << "Generated " << randomNumbers.size() << " mines";

    assert(targetMineCount == randomNumbers.size());

    qDebug() << "Random numbers ";

    for(auto& number : randomNumbers)
    {
        qDebug() << number;
    }

    for(const int& randomNumber : randomNumbers)
    {
        for(auto& mineFieldButton : mineFieldButtons)
        {
            if(randomNumber == mineFieldButton->GetFieldNumber())
            {
                mineFieldButton->setText("MINE");
                mineFieldButton->setStyleSheet("color: red");
            }
        }
    }
}
