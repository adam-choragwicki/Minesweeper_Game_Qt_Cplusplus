#include "game_window.h"
#include "ui_game_window.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>

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
        EndGame(false);
    }
}

void GameWindow::EndGame(bool isContinuePossible)
{
    QMessageBox* pMessageBox = new QMessageBox(QMessageBox::Icon::Warning, "BOOM", "Oops");

    QPushButton* p_ContinueButton = new QPushButton("Continue", pMessageBox);
    QPushButton* p_RestartButton = new QPushButton("Restart", pMessageBox);
    QPushButton* p_CloseButton = new QPushButton("Close", pMessageBox);

    pMessageBox->addButton(p_ContinueButton, QMessageBox::NoRole);
    pMessageBox->addButton(p_RestartButton, QMessageBox::NoRole);
    pMessageBox->addButton(p_CloseButton, QMessageBox::NoRole);

    if(isContinuePossible == false)
    {
        p_ContinueButton->setEnabled(false);
    }

    int userInput = pMessageBox->exec();

    enum BUTTON_MEANINGS
    {
        CONTINUE = 0,
        RESTART = 1,
        CLOSE = 2
    };

    qDebug() << "User input: " << userInput;

    if(userInput == CONTINUE)
    {
        /*This case added just for explicity*/
    }
    else if(userInput == RESTART)
    {
        QCoreApplication::exit(1);
    }
    else if(userInput == CLOSE)
    {
        exit(0);
    }
    else
    {
        assert(false);
    }
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_MainGridLayout;
}

void GameWindow::closeEvent(QCloseEvent* /*closeEvent*/)
{
    exit(0);
}
