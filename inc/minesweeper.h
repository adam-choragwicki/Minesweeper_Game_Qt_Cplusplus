#pragma once

#include "model.h"
#include "view/game_main_window.h"
#include "controller.h"

class Minesweeper : public QObject
{
Q_OBJECT

public slots:
    void processRestartEvent(bool newParametersRequested);

public:
    Minesweeper();

private:
    void subscribeToRestartEvent();

    std::unique_ptr<Model> model_;
    std::unique_ptr<GameMainWindow> view_;
    std::unique_ptr<Controller> controller_;

    MinefieldParameters minefieldParameters_;
};
