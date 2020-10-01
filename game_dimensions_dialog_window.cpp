#include "game_dimensions_dialog_window.h"
#include "ui_game_dimensions_dialog_window.h"
#include <QMessageBox>

GameDimensionsDialogWindow::GameDimensionsDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDimensionsDialogWindow)
{
    ui->setupUi(this);
}

GameDimensionsDialogWindow::~GameDimensionsDialogWindow()
{
    delete ui;
}

void GameDimensionsDialogWindow::on_buttonBox_accepted()
{
    if(ValidateInput() == true)
    {
        setResult(0);
    }
    else
    {
        setResult(-1);
    }
}

void GameDimensionsDialogWindow::on_buttonBox_rejected()
{
    exit(-1);
}

bool GameDimensionsDialogWindow::ValidateInput()
{
    std::unique_ptr<bool> conversionSuccessFlag(new bool(true));

    const int enteredRowCount = ui->rowCount_LineEdit->text().toInt(conversionSuccessFlag.get());
    const int enteredColumnCount = ui->columnCount_LineEdit->text().toInt(conversionSuccessFlag.get());

    if(*conversionSuccessFlag == false)
    {
        QMessageBox::critical(this, "Wrong data", "Only numbers accepted");
        return false;
    }

    if(!(enteredRowCount >= MIN_ROW_COUNT && enteredRowCount <= MAX_ROW_COUNT))
    {
        QMessageBox::critical(this, "Wrong dimensions", "Wrong row count: " + QString::number(enteredRowCount) + ". Expected range is " + QString::number(MIN_ROW_COUNT) + "-" + QString::number(MAX_ROW_COUNT));
        return false;;
    }

    if(!(enteredColumnCount >= MIN_COLUMN_COUNT && enteredColumnCount <= MAX_COLUMN_COUNT))
    {
        QMessageBox::critical(this, "Wrong dimensions", "Wrong column count: " + QString::number(enteredColumnCount) + ". Expected range is " + QString::number(MIN_COLUMN_COUNT) + "-" + QString::number(MAX_COLUMN_COUNT));
        return false;;
    }

    m_RowCount = enteredRowCount;
    m_ColumnCount = enteredColumnCount;

    return true;
}
