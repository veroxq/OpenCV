#include "cameragetface.h"

cameraGetFace::cameraGetFace(QWidget * parent) : QDialog(parent)
{
    label = new QLabel;
    label->setGeometry(500,500,800,800);

    button = new QPushButton("确认",this);
    connect(button,&QPushButton::clicked,this,&cameraGetFace::ok);

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(button);
    setLayout(layout);

    timer =new QTimer();
    connect(timer,&QTimer::timeout,this,&cameraGetFace::update);

}

void cameraGetFace::update()
{
   capture >> frame;
   if(!frame.empty()){
        QImage ima=QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
        label->setPixmap(QPixmap::fromImage(ima));
        label->setScaledContents(true);
   }

}
QImage cameraGetFace::getImage(){
    return faceImage;
}

void cameraGetFace::openWindow(){

    capture = cv::VideoCapture(0);

    timer->start(30);
    this->exec();
}

void cameraGetFace::ok(){
    faceImage = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
    timer->stop();
    capture.release();

    close();
}
