#include "view/field_button.h"
#include "log_manager.h"
#include "field.h"

FieldButton::FieldButton(Field* field)
{
    field_ = field;

    if(!pixmapsLoaded)
    {
        pixmapsLoaded = loadImages();
    }

    setCheckable(true);
    setFixedSize(SIZE, SIZE);

    QFont currentFont = font();
    currentFont.setPointSize(FONT_SIZE);
    currentFont.setBold(true);
    setFont(currentFont);

    render();
}

bool FieldButton::loadImages()
{
    flagPixmap = std::make_unique<QPixmap>();
    minePixmap = std::make_unique<QPixmap>();

    if(!flagPixmap->load(":/images/images/flag.png"))
    {
        throw std::runtime_error("Could not load :/images/images/flag.png");
    }

    if(!minePixmap->load(":/images/images/mine.png"))
    {
        throw std::runtime_error("Could not load :/images/images/mine.png");
    }

    return true;
}

void FieldButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        emit clickedEvent(ClickType::left, field_);
    }
    else if(event->button() == Qt::MouseButton::RightButton)
    {
        emit clickedEvent(ClickType::right, field_);
    }
}

void FieldButton::render()
{
    FieldState fieldState = field_->getState();

    if(fieldState == FieldState::FLAGGED)
    {
        setIcon(*flagPixmap);
        setChecked(false);
        setIconSize(QSize(this->width() - 5, this->height() - 5));
        setText("");
    }
    else if(fieldState == FieldState::COVERED)
    {
        setIcon(QIcon());
        setChecked(false);
        setStyleSheet("color: black");
        setIconSize(QSize(this->width() - 5, this->height() - 5));
        setText("");
    }
    else if(fieldState == FieldState::MINE_EXPLODED)
    {
        setIcon(*minePixmap);
        setChecked(false);
        setIconSize(QSize(this->width() - 2, this->height() - 2));
        setText("");
    }
    else
    {
        setIcon(QIcon());
        setChecked(true);

        auto adjacentMineCount = field_->getAdjacentMineCount();

        if(adjacentMineCount == 0)
        {
            setStyleSheet("background:rgb(240, 240, 240);");
            setText("");
        }
        else
        {
            setStyleSheet("color: black");
            setText(QString::number(adjacentMineCount.value_or(-1)));
        }
    }
}
