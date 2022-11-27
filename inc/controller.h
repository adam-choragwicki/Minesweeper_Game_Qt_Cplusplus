#pragma once

#include "model.h"
#include "view/game_main_window.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void processMousePressEvent(ClickType clickType, Field* field);

public:
    Controller(Model* model, GameMainWindow* view);

    void subscribeToFieldButtonClickedEvents();
    void subscribeFieldButtonsToFieldStateUpdatedEvents();
    void subscribeViewToGameEndEvent();

private:
    Model* model_;
    GameMainWindow* view_;
};
