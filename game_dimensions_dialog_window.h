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

    int getRowCount() const {return rowCount_;}
    int getColumnCount() const {return columnCount_;}
    int getMinePercentage() const {return minePercentage_;}

private:
    void reject() override;

    Ui::GameDimensionsDialogWindow* ui_;

    int rowCount_;
    int columnCount_;
    int minePercentage_;

private slots:
    void on_buttonBox_accepted();
};
