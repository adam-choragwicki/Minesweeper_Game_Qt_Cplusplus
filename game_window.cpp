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
            MineFieldButton* mineFieldButton = new MineFieldButton(x, y, fieldNumber, "");
            mineFieldButtons.insert(Coordinates(x, y), mineFieldButton);
            m_MainGridLayout->addWidget(mineFieldButton, x, y);
            ++fieldNumber;
        }
    }

    GenerateMines(mineFieldButtons);
    ScanForMines();
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_MainGridLayout;
}

void GameWindow::GenerateMines(QMap<Coordinates, MineFieldButton*>& mineFieldButtons) const
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
                mineFieldButton->SetMine();
                mineFieldButton->setStyleSheet("color: red");
            }
        }
    }
}

void GameWindow::ScanForMines() const
{
    for(auto& mineFieldButton : mineFieldButtons)
    {
        int adjacentMineCount = 0;

        if(mineFieldButton->IsMine())
        {
            /*If a field is mine itself an adjacent mine count is irrelevant*/
            mineFieldButton->SetAdjacentMineCount(-1);
            continue;
        }
        else
        {
            int x = mineFieldButton->GetX();
            int y = mineFieldButton->GetY();

            MineFieldButton* otherMineFieldButton = nullptr;

            QVector<Coordinates> adjacentFieldsRelativeCoordinates = {Coordinates(x, y - 1),
                                                                      Coordinates(x, y + 1),
                                                                      Coordinates(x - 1, y),
                                                                      Coordinates(x + 1, y),
                                                                      Coordinates(x - 1, y - 1),
                                                                      Coordinates(x - 1, y + 1),
                                                                      Coordinates(x + 1, y - 1),
                                                                      Coordinates(x + 1, y + 1)};

            for(auto& coordinates : adjacentFieldsRelativeCoordinates)
            {
                otherMineFieldButton = mineFieldButtons.value(coordinates, nullptr);

                if(otherMineFieldButton)
                {
                    if(otherMineFieldButton->IsMine() == true)
                    {
                        ++adjacentMineCount;
                    }
                }
            }
        }

        mineFieldButton->SetAdjacentMineCount(adjacentMineCount);
    }
}
