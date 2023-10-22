#include "initialwindow.h"

initialWindow::initialWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(2304,1296);
    backgroundImageLabel = new QLabel(this);
    QPixmap backgroundImage("D:/FACE_TEST/image/WholeWindow.png");
    backgroundImageLabel->setPixmap(backgroundImage.scaled(2304,1296,Qt::KeepAspectRatioByExpanding));
    backgroundImageLabel->setGeometry(0,0,width(),height());
}
