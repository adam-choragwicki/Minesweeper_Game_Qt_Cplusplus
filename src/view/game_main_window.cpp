#include "view/game_main_window.h"
#include "ui_game_main_window.h"
#include "view/end_game_dialog.h"
#include "log_manager.h"

GameMainWindow::GameMainWindow(Model& model, QWidget* parent) : QMainWindow(parent), ui_(new Ui::GameMainWindow), model_(&model)
{
    ui_->setupUi(this);

    mainGridLayout_.setHorizontalSpacing(0);
    mainGridLayout_.setVerticalSpacing(0);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui_->centralwidget->setLayout(&mainGridLayout_);

    createFieldButtons();
}

GameMainWindow::~GameMainWindow()
{
    delete ui_;
}

void GameMainWindow::closeEvent(QCloseEvent*)
{
    exit(0);
}

void GameMainWindow::updateFieldButtons()
{
    removeFieldButtons();
    createFieldButtons();
}

void GameMainWindow::createFieldButtons()
{
    for(auto& [coordinates, field] : model_->getCoordinatesToFieldsMapping())
    {
        coordinatesToFieldButtonsMapping.insert({coordinates, std::make_unique<FieldButton>(field.get())});
        mainGridLayout_.addWidget(coordinatesToFieldButtonsMapping.at(coordinates).get(), coordinates.getRow(), coordinates.getColumn());
    }
}

void GameMainWindow::removeFieldButtons()
{
    for(auto& [coordinates, fieldButton] : coordinatesToFieldButtonsMapping)
    {
        mainGridLayout_.removeWidget(fieldButton.get());
    }

    coordinatesToFieldButtonsMapping.clear();
}

void GameMainWindow::processGameEndSlot(GameResult gameResult)
{
    EndGameDialog endGameDialog(this, gameResult);

    if(endGameDialog.result() == static_cast<int>(EndGameDialog::ButtonRole::RESTART))
    {
        emit restartEvent(false);
    }
    else if(endGameDialog.result() == static_cast<int>(EndGameDialog::ButtonRole::CHANGE_PARAMETERS))
    {
        emit restartEvent(true);
    }
    else
    {
        close();
    }
}
