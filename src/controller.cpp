#include "controller.h"

Controller::Controller(Model* model, GameMainWindow* view)
{
    model_ = model;
    view_ = view;
}

void Controller::processMousePressEvent(ClickType clickType, Field* field)
{
    if(clickType == ClickType::left)
    {
        if(field->getState() == FieldState::COVERED)
        {
            if(field->isMinePresent())
            {
                field->setState(FieldState::MINE_EXPLODED);
                model_->processGameEnd(GameResult::lose);
            }
            else
            {
                field->uncover();

                if(field->getAdjacentMineCount() == 0)
                {
                    FieldsUncoverer::uncoverAdjacentEmptyFields(field, model_->getMinefield());
                }
            }

            if(FieldsManager::countRemainingCoveredFieldsWithoutMine(model_->getMinefield()) == 0)
            {
                model_->processGameEnd(GameResult::win);
            }
        }
    }
    else if(clickType == ClickType::right)
    {
        if(field->getState() == FieldState::COVERED)
        {
            field->setState(FieldState::FLAGGED);
        }
        else if(field->getState() == FieldState::FLAGGED)
        {
            field->setState(FieldState::COVERED);
        }
    }
}

void Controller::subscribeToFieldButtonClickedEvents()
{
    auto& fieldButtons = view_->getFieldButtons();

    for(auto& [coordinates, fieldButton] : fieldButtons)
    {
        connect(fieldButton.get(), &FieldButton::clickedEvent, this, &Controller::processMousePressEvent);
    }
}

void Controller::subscribeFieldButtonsToFieldStateUpdatedEvents()
{
    auto& fieldButtons = view_->getFieldButtons();

    for(auto& [coordinates, fieldButton] : fieldButtons)
    {
        connect(fieldButton.get()->getField(), &Field::fieldStateUpdatedEvent, fieldButton.get(), &FieldButton::render);
    }
}

void Controller::subscribeViewToGameEndEvent()
{
    connect(model_, &Model::gameEndEvent, view_, &GameMainWindow::processGameEndSlot);
}
