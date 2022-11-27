#pragma once

#include "common.h"
#include "coordinates.h"

#include <QPushButton>
#include <QMouseEvent>

class FieldButton : public QPushButton
{
Q_OBJECT

signals:
    void clickedEvent(ClickType clickType, Field*);

public slots:
    void render();

public:
    explicit FieldButton(Field* field);

    [[nodiscard]] Field* getField() const
    { return field_; };

private:
    void mousePressEvent(QMouseEvent* event) override;

    static bool loadImages();

    inline static std::unique_ptr<QPixmap> flagPixmap;
    inline static std::unique_ptr<QPixmap> minePixmap;

    inline static bool pixmapsLoaded = false;

    Field* field_;

    const int SIZE = 30;
    const int FONT_SIZE = 20;
};
