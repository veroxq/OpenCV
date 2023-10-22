#include "optionbutton.h"

OptionButton::OptionButton(QWidget *parent)
    : QPushButton(parent)
{
    condition = true;
}

void OptionButton::setImages(const QString &normalImagePath, const QString &highlightImagePath){
    normalImage = normalImagePath;
    highlightImage = highlightImagePath;
}

void OptionButton::reset()
{
    if(condition==false) return;

    condition=false;
    QPixmap image(normalImage);
    QPixmap scaledImage = image.scaled(this->size(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    this->setIcon(scaledImage);
    this->setIconSize(this->size());
}

void OptionButton::set()
{
    if(condition==true) return;

    condition=true;
    QPixmap image(highlightImage);
    QPixmap scaledImage = image.scaled(this->size(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    this->setIcon(scaledImage);
    this->setIconSize(this->size());
}
