#include "game_dimensions_dialog_window.h"
#include "ui_game_dimensions_dialog_window.h"
#include "common.h"

GameDimensionsDialogWindow::GameDimensionsDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::GameDimensionsDialogWindow)
{
    ui_->setupUi(this);

    for(int i = 0, rowCountOption = gameParametersLimits::minRowCount; rowCountOption <= gameParametersLimits::maxRowCount; ++rowCountOption, ++i)
    {
        ui_->rowCount_ComboBox->addItem(QString::number(rowCountOption));
        ui_->rowCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    for(int i = 0, columnCountOption = gameParametersLimits::minColumnCount; columnCountOption <= gameParametersLimits::maxColumnCount; ++columnCountOption, ++i)
    {
        ui_->columnCount_ComboBox->addItem(QString::number(columnCountOption));
        ui_->columnCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    for (int i = 0 ; i < gameParametersLimits::minePercentageOptions.size() ; ++i)
    {
        ui_->minesPercentage_ComboBox->addItem(QString::number(gameParametersLimits::minePercentageOptions.at(i)));
        ui_->minesPercentage_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}

GameDimensionsDialogWindow::~GameDimensionsDialogWindow()
{
    delete ui_;
}

void GameDimensionsDialogWindow::on_buttonBox_accepted()
{
    gameParameters_ = std::make_unique<GameParameters>(ui_->rowCount_ComboBox->currentText().toInt(),
                                                       ui_->columnCount_ComboBox->currentText().toInt(),
                                                       ui_->minesPercentage_ComboBox->currentText().toInt());
}

void GameDimensionsDialogWindow::reject()
{
    exit(0);
}