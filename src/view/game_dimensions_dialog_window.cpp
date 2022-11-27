#include "view/game_dimensions_dialog_window.h"
#include "ui_game_dimensions_dialog_window.h"

GameDimensionsDialogWindow::GameDimensionsDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::GameDimensionsDialogWindow)
{
    ui_->setupUi(this);

    for(int i = 0, rowCountOption = GameParametersLimits::minRowCount; rowCountOption <= GameParametersLimits::maxRowCount; ++rowCountOption, ++i)
    {
        ui_->rowCount_ComboBox->addItem(QString::number(rowCountOption));
        ui_->rowCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    for(int i = 0, columnCountOption = GameParametersLimits::minColumnCount; columnCountOption <= GameParametersLimits::maxColumnCount; ++columnCountOption, ++i)
    {
        ui_->columnCount_ComboBox->addItem(QString::number(columnCountOption));
        ui_->columnCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    for (int i = 0 ; i < GameParametersLimits::minePercentageOptions.size() ; ++i)
    {
        ui_->minesPercentage_ComboBox->addItem(QString::number(GameParametersLimits::minePercentageOptions.at(i)));
        ui_->minesPercentage_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}

GameDimensionsDialogWindow::~GameDimensionsDialogWindow()
{
    delete ui_;
}

void GameDimensionsDialogWindow::on_buttonBox_accepted()
{
    gameParameters_ = std::make_unique<MinefieldParameters>(ui_->rowCount_ComboBox->currentText().toInt(),
                                                            ui_->columnCount_ComboBox->currentText().toInt(),
                                                            ui_->minesPercentage_ComboBox->currentText().toInt());
}

void GameDimensionsDialogWindow::reject()
{
    exit(0);
}
