#pragma once

#include "coordinates.h"
#include "common.h"

#include <QPushButton>
#include <QMouseEvent>

class Field : public QPushButton
{
    Q_OBJECT
public:
    Field(int x, int y);

    static void loadImages();

    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}
    [[nodiscard]] bool isFlagged() const {return flagged_;}
    [[nodiscard]] bool isUncovered() const {return uncovered_;}
    [[nodiscard]] bool isMine() const {return mineIsPresent_;}

    void setAdjacentMineCount(int adjacentMineCount) {adjacentMineCount_ = adjacentMineCount;}
    void setMine();

    void reset();
    void toggleFlag();
    int uncover();

signals:
    void clickedSignal(ClickType clickType, const Coordinates& coordinates);

private:
    void mousePressEvent(QMouseEvent* event) override;

    void showAdjacentMineCount();
    void showFlag();
    void showMine();

    static std::unique_ptr<QPixmap> flagPixmap;
    static std::unique_ptr<QPixmap> minePixmap;

    const int size_ = 30;
    const int fontSize_ = 20;
    const Coordinates coordinates_;
    const QString textDefaultColor_ = "color: black";

    bool mineIsPresent_{};
    bool uncovered_{};
    bool flagged_{};
    int adjacentMineCount_{};
};
