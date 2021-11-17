#pragma once

#include "common.h"

#include <QMessageBox>

class EndGameDialog : public QMessageBox
{
public:
    EndGameDialog(QWidget* parent, GameResult gameResult);
};
