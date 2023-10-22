
#include "databasewindow.h"

dataFaceWindow::dataFaceWindow(QWidget *parent) : QWidget(parent)
{
    condition = false;

    setFixedSize(2304,1296);
    backgroundImageLabel = new QLabel(this);
    QPixmap backgroundImage("D:/FACE_TEST/image/WholeWindow_face&smileTest.png");
    backgroundImageLabel->setPixmap(backgroundImage.scaled(2304,1296,Qt::KeepAspectRatioByExpanding));
    backgroundImageLabel->setGeometry(0,0,width(),height());

}

void dataBaseWindow::showTrue(){
    if(condition) return;
    condition = true;
    this->show();
}

void dataFaceWindow::showFalse()
{
    if(!condition) return;
    condition = false;
    this->hide();
}

void dataFaceWindow::getPictureClicked()
{

}

void dataFaceWindow::getVedioClicked()
{

}

void dataFaceWindow::getCameraClicked()
{

}

