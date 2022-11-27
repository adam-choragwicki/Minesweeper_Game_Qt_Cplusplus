#pragma once

#include "model.h"
#include "field.h"
#include "common.h"
#include "field_button.h"

#include <QMainWindow>
#include "QGridLayout"

using CoordinatesToFieldButtonsMapping = std::map<Coordinates, std::unique_ptr<FieldButton>>;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class GameMainWindow;
}
QT_END_NAMESPACE

class GameMainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void restartEvent(bool newParametersRequested);

public slots:
    void processGameEndSlot(GameResult gameResult);

public:
    explicit GameMainWindow(Model& model, QWidget* parent = nullptr);
    ~GameMainWindow() override;

    void updateFieldButtons();

    const CoordinatesToFieldButtonsMapping& getFieldButtons() const
    { return coordinatesToFieldButtonsMapping; }

private:
    void closeEvent(QCloseEvent*) override;

    void createFieldButtons();
    void removeFieldButtons();

    Ui::GameMainWindow* ui_;
    QGridLayout mainGridLayout_;
    Model* model_;

    CoordinatesToFieldButtonsMapping coordinatesToFieldButtonsMapping;
};
