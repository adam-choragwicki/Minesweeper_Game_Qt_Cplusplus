#include "field.h"
#include "end_game_dialog.h"

#include <QMessageBox>
#include <QApplication>

std::unique_ptr<QPixmap> Field::flagPixmap;
std::unique_ptr<QPixmap> Field::minePixmap;

Field::Field(int x, int y) :
    coordinates_(x, y)
{
    setCheckable(true);
    setFixedSize(size_, size_);

    QFont currentFont = font();
    currentFont.setPointSize(fontSize_);
    currentFont.setBold(true);
    setFont(currentFont);

    reset();
}

void Field::loadImages()
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
}

void Field::reset()
{
    setChecked(false);
    setText("");
    setStyleSheet(textDefaultColor_);
    setIcon(QIcon());

    mineIsPresent_ = false;
    covered_ = true;
    flagged_ = false;
    adjacentMineCount_ = 0;
}

void Field::setMine()
{
    if(!mineIsPresent_)
    {
        mineIsPresent_ = true;
    }
    else
    {
        throw std::logic_error("Error, trying to put mine on a field already containing mine.");
    }
}

void Field::toggleFlag()
{
    if(flagged_)
    {
        setIcon(QIcon());
        flagged_ = false;
    }
    else
    {
        showFlag();
        flagged_ = true;
    }
}

int Field::uncover()
{
    if(mineIsPresent_)
    {
        showMine();
        return -1;
    }
    else
    {
        showAdjacentMineCount();
        covered_ = false;
        return adjacentMineCount_;
    }
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

void Field::showAdjacentMineCount()
{
    if(adjacentMineCount_ == 0)
    {
        setChecked(true);
        setStyleSheet("background:rgb(240, 240, 240);");
    }
    else
    {
        setStyleSheet("color: black");
        setText(QString::number(adjacentMineCount_));
    }
}

void Field::showFlag()
{
    setIcon(*flagPixmap);
    setIconSize(QSize(this->width() - 5, this->height() - 5));
}

void Field::showMine()
{
    setIcon(*minePixmap);
    setIconSize(QSize(this->width() - 2, this->height() - 2));
}
