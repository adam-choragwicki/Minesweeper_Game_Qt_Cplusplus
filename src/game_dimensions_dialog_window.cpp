#include "game_dimensions_dialog_window.h"
#include "ui_game_dimensions_dialog_window.h"
#include "common.h"

#include <QMessageBox>
#include <QLineEdit>

GameDimensionsDialogWindow::GameDimensionsDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::GameDimensionsDialogWindow)
{
    ui_->setupUi(this);

    QStringList rowCountOptions;

    for(int i = gameParameters::minRowCount; i <= gameParameters::maxRowCount; i++)
    {
        rowCountOptions.append(QString::number(i));
    }

    ui_->rowCount_ComboBox->addItems(rowCountOptions);

    for (int i = 0 ; i < ui_->rowCount_ComboBox->count() ; ++i)
    {
        ui_->rowCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    QStringList columnCountOptions;

    for(int i = gameParameters::minColumnCount; i <= gameParameters::maxColumnCount; i++)
    {
        columnCountOptions.append(QString::number(i));
    }

    ui_->columnCount_ComboBox->addItems(columnCountOptions);

    for (int i = 0 ; i < ui_->columnCount_ComboBox->count() ; ++i)
    {
        ui_->columnCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    QStringList minePercentageOptions {"10", "20", "30"};
    ui_->minesPercentage_ComboBox->addItems(minePercentageOptions);

    for (int i = 0 ; i < ui_->minesPercentage_ComboBox->count() ; ++i)
    {
        ui_->minesPercentage_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}

GameDimensionsDialogWindow::~GameDimensionsDialogWindow()
{
    delete ui_;
}

void GameDimensionsDialogWindow::reject()
{
    exit(0);
}

void GameDimensionsDialogWindow::on_buttonBox_accepted()
{
    rowCount_ = ui_->rowCount_ComboBox->currentText().toInt();
    columnCount_ = ui_->columnCount_ComboBox->currentText().toInt();
    minePercentage_ = ui_->minesPercentage_ComboBox->currentText().toInt();
}
