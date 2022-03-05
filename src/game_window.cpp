#include "game_window.h"
#include "ui_game_window.h"
#include "end_game_dialog.h"
#include "common.h"

GameWindow::GameWindow(GameEngine& gameEngine, QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::GameWindow),
      gameEngine_(gameEngine)
{
    ui_->setupUi(this);

    mainGridLayout_.setHorizontalSpacing(0);
    mainGridLayout_.setVerticalSpacing(0);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui_->centralwidget->setLayout(&mainGridLayout_);

    connect(&gameEngine_, &GameEngine::drawFieldsSignal, this, &GameWindow::drawFieldsSlot);
    connect(&gameEngine_, &GameEngine::connectFieldsProcessingSignal, this, &GameWindow::connectFieldsProcessingSlot);
    connect(&gameEngine_, &GameEngine::gameEndSignal, this, &GameWindow::processGameEndSlot);

    gameEngine.restartGame();
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::closeEvent(QCloseEvent*)
{
    exit(0);
}

void GameWindow::drawFieldsSlot()
{
    for (const auto& field: gameEngine_.getCoordinatesToFieldsMapping())
    {
        const int x = field->getCoordinates().getRow();
        const int y = field->getCoordinates().getColumn();

        mainGridLayout_.addWidget(field.get(), x, y);
    }
}

void GameWindow::connectFieldsProcessingSlot()
{
    for (const auto& field: gameEngine_.getCoordinatesToFieldsMapping())
    {
        connect(field.get(), &Field::clickedSignal, this, &GameWindow::processFieldClickedSlot);
    }
}

void GameWindow::processFieldClickedSlot(ClickType clickType, const Coordinates& coordinates)
{
    std::shared_ptr<Field> field = gameEngine_.getCoordinatesToFieldsMapping()[coordinates];

    if(clickType == ClickType::left)
    {
        gameEngine_.processLeftClick(field);
    }
    else if(clickType == ClickType::right)
    {
        gameEngine_.processRightClick(field);
    }
}

void GameWindow::processGameEndSlot(GameResult gameResult)
{
    EndGameDialog endGameDialog(this, gameResult);

    if(endGameDialog.result() == QMessageBox::Reset)
    {
        gameEngine_.restartGame();
    }
    else
    {
        close();
    }
}
