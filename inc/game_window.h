#pragma once

#include "game_engine.h"
#include "field.h"
#include "common.h"

#include <QMainWindow>
#include "QGridLayout"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(const GameParameters&& gameParameters, QWidget* parent = nullptr);
    ~GameWindow() override;

private:
    void closeEvent(QCloseEvent*) override;

    void drawFields();

    Ui::GameWindow *ui_;
    QGridLayout mainGridLayout_;
    std::unique_ptr<GameEngine> gameEngine_;

private slots:
    void processFieldClicked(ClickType clickType, const Coordinates& coordinates);
    void processGameEnd(GameResult gameResult);
};
