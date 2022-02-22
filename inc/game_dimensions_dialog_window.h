#pragma once

#include <QDialog>
#include "common.h"

namespace Ui {
class GameDimensionsDialogWindow;
}

class GameDimensionsDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameDimensionsDialogWindow(QWidget* parent = nullptr);
    ~GameDimensionsDialogWindow() override;

    [[nodiscard]] GameParameters getGameParameters() const {return gameParameters_;}

private:
    void reject() override;

    Ui::GameDimensionsDialogWindow* ui_;
    GameParameters gameParameters_;

private slots:
    void on_buttonBox_accepted();
};
