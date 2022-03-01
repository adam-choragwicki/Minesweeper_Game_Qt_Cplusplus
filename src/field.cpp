#include "field.h"
#include "end_game_dialog.h"

#include <QMessageBox>
#include <QApplication>

Field::Field(int x, int y) :
    coordinates_(x, y)
{
    if(!pixmapsLoaded)
    {
        pixmapsLoaded = loadImages();
    }

    const int size_ = 30;
    const int fontSize_ = 20;

    setCheckable(true);
    setFixedSize(size_, size_);

    QFont currentFont = font();
    currentFont.setPointSize(fontSize_);
    currentFont.setBold(true);
    setFont(currentFont);

    reset();
}

bool Field::loadImages()
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

void Field::reset()
{
    setChecked(false);
    setText("");

    const QString textDefaultColor_ = "color: black";
    setStyleSheet(textDefaultColor_);

    setIcon(QIcon());

    mineIsPresent_ = false;
    covered_ = true;
    flagged_ = false;
    adjacentMineCount_ = std::nullopt;
}

void Field::placeMine()
{
    if(!mineIsPresent_)
    {
        mineIsPresent_ = true;
    }
    else
    {
        throw std::runtime_error("Cannot put mine on a field already containing mine.");
    }
}

void Field::toggleFlag()
{
    if(flagged_)
    {
        flagged_ = false;
    }
    else
    {
        flagged_ = true;
    }

    frontendToggleFlag();
}

std::optional<int> Field::uncover(bool removeFlag)
{
    std::optional<int> returnValue;

    if(removeFlag && flagged_)
    {
        toggleFlag();
    }

    if(mineIsPresent_)
    {
        returnValue = std::nullopt;
    }
    else
    {
        covered_ = false;
        returnValue = adjacentMineCount_.value_or(-1);
    }

    frontendUncover();

    return returnValue;
}

void Field::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        emit clickedSignal(ClickType::left, coordinates_);
    }
    else if(event->button() == Qt::MouseButton::RightButton)
    {
        emit clickedSignal(ClickType::right, coordinates_);
    }
}

void Field::frontendUncover()
{
    if(mineIsPresent_)
    {
        setIcon(*minePixmap);
        setIconSize(QSize(this->width() - 2, this->height() - 2));
    }
    else
    {
        if(adjacentMineCount_ == 0)
        {
            setChecked(true);
            setStyleSheet("background:rgb(240, 240, 240);");
        }
        else
        {
            setStyleSheet("color: black");
            setText(QString::number(adjacentMineCount_.value_or(-1)));
        }
    }
}

void Field::frontendShowFlag()
{
    setIcon(*flagPixmap);
    setIconSize(QSize(this->width() - 5, this->height() - 5));
}

void Field::frontendRemoveFlag()
{
    setIcon(QIcon());
    setIconSize(QSize(this->width() - 5, this->height() - 5));
}

void Field::frontendToggleFlag()
{
    if(flagged_)
    {
        frontendShowFlag();
    }
    else
    {
        frontendRemoveFlag();
    }
}