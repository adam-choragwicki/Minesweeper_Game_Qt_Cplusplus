#include "game_window.h"
#include "ui_game_window.h"
#include "end_game_dialog.h"
#include "common.h"

#include <QDebug>

GameWindow::GameWindow(int rowCount, int columnCount, int minePercentage, QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::GameWindow),
      rowCount_(rowCount),
      columnCount_(columnCount),
      minePercentage_(minePercentage)
{
    ui_->setupUi(this);

    mainGridLayout_.setHorizontalSpacing(0);
    mainGridLayout_.setVerticalSpacing(0);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui_->centralwidget->setLayout(&mainGridLayout_);

    Field::loadImages();
    createFields();

    gameEngine_ = std::make_unique<GameEngine>(rowCount_, columnCount_, minePercentage_, mineFieldButtons_);

    connect(gameEngine_.get(), &GameEngine::gameEnd, this, &GameWindow::processGameEnd);
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::closeEvent(QCloseEvent*)
{
    exit(0);
}

void GameWindow::createFields()
{
    for(int x = 1; x <= rowCount_; x++)
    {
        for(int y = 1; y <= columnCount_; y++)
        {
            std::shared_ptr<Field> mineFieldButton = std::make_shared<Field>(x, y);
            mineFieldButtons_.insert(Coordinates(x, y),  mineFieldButton);
            mainGridLayout_.addWidget(mineFieldButton.get(), x, y);

            connect(mineFieldButton.get(), &Field::clicked, this, &GameWindow::processFieldClicked);
        }
    }
}

void GameWindow::processFieldClicked(ClickType clickType, const Coordinates& coordinates)
{
    std::shared_ptr<Field> field = mineFieldButtons_[coordinates];

    if(clickType == ClickType::left)
    {
        gameEngine_->processLeftClick(field);
    }
    else if(clickType == ClickType::right)
    {
        gameEngine_->processRightClick(field);
    }
}

void GameWindow::processGameEnd(GameResult gameResult)
{
    EndGameDialog endGameDialog(this, gameResult);

    if(endGameDialog.result() == QMessageBox::Reset)
    {
        gameEngine_->restartGame();
    }
    else
    {
        close();
    }
}
