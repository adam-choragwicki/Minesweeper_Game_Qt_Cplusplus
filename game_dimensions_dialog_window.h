#pragma once

#include <QDialog>

namespace Ui {
class GameDimensionsDialogWindow;
}

class GameDimensionsDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameDimensionsDialogWindow(QWidget* parent = nullptr);
    ~GameDimensionsDialogWindow();
    int GetRowCount() {return m_RowCount;}
    int GetColumnCount() {return m_ColumnCount;}

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::GameDimensionsDialogWindow* ui;

    const int MIN_ROW_COUNT = 10;
    const int MAX_ROW_COUNT = 30;
    const int MIN_COLUMN_COUNT = 10;
    const int MAX_COLUMN_COUNT = 30;

    int m_RowCount;
    int m_ColumnCount;

    bool ValidateInput();

    void closeEvent(QCloseEvent* closeEvent) override;
};
