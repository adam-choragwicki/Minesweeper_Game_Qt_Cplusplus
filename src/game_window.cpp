#include "game_window.h"
#include "ui_game_window.h"
#include "end_game_dialog.h"
#include "common.h"

#include <QDebug>

GameWindow::GameWindow(const GameParameters&& gameParameters, QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);

    mainGridLayout_.setHorizontalSpacing(0);
    mainGridLayout_.setVerticalSpacing(0);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui_->centralwidget->setLayout(&mainGridLayout_);

    Field::loadImages();

    gameEngine_ = std::make_unique<GameEngine>(gameParameters);

    drawFields();

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

void GameWindow::drawFields()
{
    for (const auto& field: gameEngine_->getCoordinatesToFieldsMapping())
    {
        const int x = field->getCoordinates().getRow();
        const int y = field->getCoordinates().getColumn();

        mainGridLayout_.addWidget(field.get(), x, y);
        connect(field.get(), &Field::clickedSignal, this, &GameWindow::processFieldClicked);
    }
}

void GameWindow::processFieldClicked(ClickType clickType, const Coordinates& coordinates)
{
    std::shared_ptr<Field> field = gameEngine_->getCoordinatesToFieldsMapping()[coordinates];

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
