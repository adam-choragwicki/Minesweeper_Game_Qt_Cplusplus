#include "minesweeper.h"
#include "view/game_dimensions_dialog_window.h"

Minesweeper::Minesweeper()
{
    GameDimensionsDialogWindow gameDimensionsDialogWindow;
    gameDimensionsDialogWindow.exec();

    minefieldParameters_ = gameDimensionsDialogWindow.getGameParameters();

    model_ = std::make_unique<Model>(minefieldParameters_);
    view_ = std::make_unique<GameMainWindow>(*model_);
    controller_ = std::make_unique<Controller>(model_.get(), view_.get());

    controller_->subscribeToFieldButtonClickedEvents();
    controller_->subscribeFieldButtonsToFieldStateUpdatedEvents();
    controller_->subscribeViewToGameEndEvent();

    subscribeToRestartEvent();

    view_->show();
}

void Minesweeper::subscribeToRestartEvent()
{
    connect(view_.get(), &GameMainWindow::restartEvent, this, &Minesweeper::processRestartEvent);
}

void Minesweeper::processRestartEvent(bool newParametersRequested)
{
    if(newParametersRequested)
    {
        GameDimensionsDialogWindow gameDimensionsDialogWindow;
        gameDimensionsDialogWindow.exec();
        minefieldParameters_ = gameDimensionsDialogWindow.getGameParameters();
    }

    model_->update(minefieldParameters_);
    view_->updateFieldButtons();

    controller_->subscribeToFieldButtonClickedEvents();
    controller_->subscribeFieldButtonsToFieldStateUpdatedEvents();
}
