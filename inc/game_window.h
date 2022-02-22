#pragma once

#include "game_engine.h"
#include "field.h"

#include <QMainWindow>
#include "QGridLayout"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(int rowCount, int columnCount, int minePercentage, QWidget* parent = nullptr);
    ~GameWindow() override;

private:
    void closeEvent(QCloseEvent*) override;

    void createFields();

    Ui::GameWindow *ui_;
    QGridLayout mainGridLayout_;
    QMap<Coordinates, std::shared_ptr<Field>> mineFieldButtons_;
    std::unique_ptr<GameEngine> gameEngine_;

    const int rowCount_;
    const int columnCount_;
    const int minePercentage_;

private slots:
    void processFieldClicked(ClickType clickType, const Coordinates& coordinates);
    void processGameEnd(GameResult gameResult);
};
