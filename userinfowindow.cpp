#include "userinfowindow.h"
#include <QDebug>

userInfoWindow::userInfoWindow(QWidget * parent) : QWidget(parent)
{
    setFixedSize(2304,1296);
    backgroundImageLabel = new QLabel(this);
    QPixmap backgroundImage("D:/FACE_TEST/image/userInfoWindow-2.png");
    backgroundImageLabel->setPixmap(backgroundImage.scaled(2304,1296,Qt::KeepAspectRatioByExpanding));
    backgroundImageLabel->setGeometry(0,0,width(),height());

    nameLabel = new QLabel(this);
    nameLabel->setGeometry(950,470,250,50);

    idLabel = new QLabel(this);
    idLabel->setGeometry(1085,555,1000,50);

    genderLabel  = new QLabel(this);
    genderLabel->setGeometry(1470,470,100,50);

    ageLabel = new QLabel(this);
    ageLabel->setGeometry(1930,470,100,50);


    faceLabel = new QLabel(this);
    faceLabel->setGeometry(1090,630,530,530);

    closeButton = new QPushButton(this);
    closeButton->setGeometry(1300,1180,100,50);
    closeButton->setText("返回");
    connect(closeButton,&QPushButton::clicked,this,&userInfoWindow::close);

    this->hide();
}

void userInfoWindow::set(userInfo user)
{

    nameLabel->setTextFormat(Qt::RichText);
    QString nameFormat="<span style=\"font-size:50px;\"><b>"+user.name+"<b></span>";
    nameLabel->setText(nameFormat);

    idLabel->setTextFormat(Qt::RichText);
    QString idFormat="<span style=\"font-size:55px;\">"+user.id+"</span>";
    idLabel->setText(idFormat);
    idLabel->setStyleSheet("QLineEdit { background-color: transparent; }");

    genderLabel->setTextFormat(Qt::RichText);
    QString genderFormat="<span style=\"font-size:50px;\"><b>"+user.gender+"<b></span>";
    genderLabel->setText(genderFormat);

    ageLabel->setTextFormat(Qt::RichText);
    QString ageFormat="<span style=\"font-size:55px;\">"+user.age+"</span>";
    ageLabel->setText(ageFormat);

    QImage qimage(user.face.data,user.face.cols,user.face.rows,user.face.step, QImage::Format_RGB888);

    QImage scaledImage = qimage.scaled(faceLabel->size(),Qt::KeepAspectRatioByExpanding);
    faceLabel->setPixmap(QPixmap::fromImage(scaledImage));

    showWindow();
}

void userInfoWindow::showWindow()
{
    this->show();
}

void userInfoWindow::hideWindow()
{
    this->hide();
}
