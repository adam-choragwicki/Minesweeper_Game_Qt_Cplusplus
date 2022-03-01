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

    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}
    [[nodiscard]] std::optional<int> getAdjacentMineCount() const {return adjacentMineCount_;}
    [[nodiscard]] bool isFlagged() const {return flagged_;}
    [[nodiscard]] bool isCovered() const {return covered_;}
    [[nodiscard]] bool isMine() const {return mineIsPresent_;}

    void setAdjacentMineCount(std::optional<int> adjacentMineCount) {adjacentMineCount_ = adjacentMineCount;}
    void placeMine();
    void reset();

    void toggleFlag();
    std::optional<int> uncover(bool removeFlag=false);

    void frontendToggleFlag();
    void frontendShowFlag();
    void frontendRemoveFlag();
    void frontendUncover();

signals:
    void clickedSignal(ClickType clickType, const Coordinates& coordinates);

private:
    void mousePressEvent(QMouseEvent* event) override;

    static bool loadImages();

    inline static std::unique_ptr<QPixmap> flagPixmap;
    inline static std::unique_ptr<QPixmap> minePixmap;
    inline static bool pixmapsLoaded = false;

    const Coordinates coordinates_;

    bool mineIsPresent_{};
    bool covered_{};
    bool flagged_{};
    std::optional<int> adjacentMineCount_{};
};
