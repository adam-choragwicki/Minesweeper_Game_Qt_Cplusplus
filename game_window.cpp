#include "game_window.h"
#include "ui_game_window.h"
#include "end_game_dialog.h"
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

    for(int x = 1; x <= ROW_COUNT; x++)
    {
        for(int y = 1; y <= COLUMN_COUNT; y++)
        {
            MineFieldButton* mineFieldButton = new MineFieldButton(x, y, "");
            mineFieldButtons.insert(MineFieldButton::Coordinates(x, y), mineFieldButton);
            m_MainGridLayout->addWidget(mineFieldButton, x, y);

            connect(mineFieldButton, &MineFieldButton::FieldClicked, this, &GameWindow::GameTick);
        }
    }

    GenerateMines(mineFieldButtons);
    ScanForMines();
}

void GameWindow::GenerateMines(QMap<MineFieldButton::Coordinates, MineFieldButton*>& mineFieldButtons) const
{
    const int targetMineCount = ROW_COUNT * COLUMN_COUNT * MINE_COVERAGE_PERCENTAGE;

    qDebug() << "Target mine count: " << targetMineCount;

    QRandomGenerator* pRandomGenerator = QRandomGenerator::global();

    QSet<MineFieldButton::Coordinates> minesCoordinates;

    while(minesCoordinates.size() != targetMineCount)
    {
        minesCoordinates.insert(MineFieldButton::Coordinates(pRandomGenerator->bounded(1, ROW_COUNT), pRandomGenerator->bounded(1, COLUMN_COUNT)));
    }

    qDebug() << "Generated " << minesCoordinates.size() << " mines";

    assert(targetMineCount == minesCoordinates.size());

    qDebug() << "Mines coordinates ";

    for(auto& mineCoordinates : minesCoordinates)
    {
        qDebug() << mineCoordinates;
    }

    for(auto& mineCoordinates : minesCoordinates)
    {
        for(auto& mineFieldButton : mineFieldButtons)
        {
            if(mineCoordinates == mineFieldButton->GetCoordinates())
            {
                mineFieldButton->SetMine();
                break;
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
            MineFieldButton::Coordinates coordinates = mineFieldButton->GetCoordinates();
            int x = coordinates.first;
            int y = coordinates.second;

            MineFieldButton* otherMineFieldButton = nullptr;

            QVector<MineFieldButton::Coordinates> adjacentFieldsRelativeCoordinates = {MineFieldButton::Coordinates(x, y - 1),
                                                                                       MineFieldButton::Coordinates(x, y + 1),
                                                                                       MineFieldButton::Coordinates(x - 1, y),
                                                                                       MineFieldButton::Coordinates(x + 1, y),
                                                                                       MineFieldButton::Coordinates(x - 1, y - 1),
                                                                                       MineFieldButton::Coordinates(x - 1, y + 1),
                                                                                       MineFieldButton::Coordinates(x + 1, y - 1),
                                                                                       MineFieldButton::Coordinates(x + 1, y + 1)};

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

int GameWindow::CountFieldsWithoutMine()
{
    int counter = 0;

    for(auto& mineFieldButton : mineFieldButtons)
    {
        if((!mineFieldButton->IsMine()) && !mineFieldButton->IsAlreadyScanned())
        {
            ++counter;
        }
    }

    return counter;
}

void GameWindow::GameTick()
{
    qDebug() << "GAME TICK";

    int fieldsWithoutMineLeft = CountFieldsWithoutMine();

    qDebug() << "Empty fields left: " << fieldsWithoutMineLeft;

    if(fieldsWithoutMineLeft == 0)
    {
        EndGameDialog(true);
    }
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_MainGridLayout;

    /*Mine field buttons should be deleted when deleting layout*/
}

void GameWindow::closeEvent(QCloseEvent* /*closeEvent*/)
{
    exit(0);
}
