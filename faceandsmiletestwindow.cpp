#include "faceandsmiletestwindow.h"
#include <QTimer>
#include <QDebug>
faceAndSmileTestWindow::faceAndSmileTestWindow(QWidget *parent) : QWidget(parent)
{
    //标记状态
    condition = false;
    contentModeCondition = 0;
    handleModeCondition = 0;

    //整体页面
    setFixedSize(2304,1296);
    backgroundImageLabel = new QLabel(this);
    QPixmap backgroundImage("D:/FACE_TEST/image/WholeWindow_face&smileTest.png");
    backgroundImageLabel->setPixmap(backgroundImage.scaled(2304,1296,Qt::KeepAspectRatioByExpanding));
    backgroundImageLabel->setGeometry(0,0,width(),height());

    //三个添加文件按钮及文本
    getPictureButton = new QPushButton("打开图片",this);
    connect(getPictureButton,&QPushButton::clicked,this,&faceAndSmileTestWindow::getPictureClicked);
    getPictureButton->setGeometry(1845,440,105,50);
    getPictureText = new QLineEdit("请选择图片",this);
    getPictureText->setReadOnly(true);
    getPictureText->setGeometry(1965,440,250,50);

    getVideoButton = new QPushButton("打开视频",this);
    connect(getVideoButton,&QPushButton::clicked,this,&faceAndSmileTestWindow::getVideoClicked);
    getVideoButton->setGeometry(1845,550,105,50);
    getVideoText = new QLineEdit("请选择视频",this);
    getVideoText->setReadOnly(true);
    getVideoText->setGeometry(1965,550,250,50);

    getCameraButton = new QPushButton("摄像头",this);
    connect(getCameraButton,&QPushButton::clicked,this,&faceAndSmileTestWindow::getCameraClicked);
    getCameraButton->setGeometry(1845,650,105,50);

    getCameraText = new QLineEdit("打开摄像头",this);
    getCameraText->setReadOnly(true);
    getCameraText->setGeometry(1965,650,250,50);

    //开始按钮
    workStartButton = new QPushButton("",this);
    workStartButton->setGeometry(1000,1124,324,97);
    QPixmap image("D:/FACE_TEST/image/WorkStartButton.png");
    QPixmap scaledImage = image.scaled(300,90,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    workStartButton->setIcon(scaledImage);
    workStartButton->setIconSize(scaledImage.size());
    
    connect(workStartButton,&QPushButton::clicked,this,&faceAndSmileTestWindow::work);

    //图片显示
    imageLabel = new QLabel(this);

    QPixmap pixmap("D:/test.png");
    QPixmap sca=pixmap.scaled(688,687,Qt::KeepAspectRatioByExpanding);

    imageLabel->setGeometry(840,365,688,687);

    this->hide();
}

void faceAndSmileTestWindow::showImage(QImage qimage){
    QImage scaledImage = qimage.scaled(imageLabel->size(),Qt::KeepAspectRatioByExpanding);
    imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void faceAndSmileTestWindow::init(){

    contentPath="";
    contentModeCondition=0;
    worktrue=false;
    cameraOpen = false;
    getPictureText->setText("请选择图片");
    getVideoText->setText("请选择视频");
    getCameraText->setText("打开摄像头");

    QImage ima("D:/FACE_TEST/image/empty_picture.png");
    showImage(ima);

    if(capture.isOpened()) capture.release();
}

void faceAndSmileTestWindow::showTrue()
{
    init();
    worktrue = false;
    if(condition) return;
    condition = true;
    this->show();
}

void faceAndSmileTestWindow::showFalse()
{
    if(!condition) return;
    condition = false;
    this->hide();
}

void faceAndSmileTestWindow::getPictureClicked()
{
    init();
    contentPath = QFileDialog::getOpenFileName(this,"选择图片",QString(),"图片文件 (*.png *.jpg *.jpeg)");
    if(!contentPath.isEmpty()){
        contentModeCondition=1;
        getPictureText->setText(contentPath);
        QImage image;
        image.load(contentPath);
        showImage(image);
    }
}

void faceAndSmileTestWindow::getVideoClicked()
{
    init();
    contentPath = QFileDialog::getOpenFileName(this, "选择视频", QString(), "视频文件 (*.mp4)");
    if (!contentPath.isEmpty()) {
        contentModeCondition=2;
        getVideoText->setText(contentPath);
        QImage ima("D:/FACE_TEST/image/video.png");
        showImage(ima);
    }
}

void faceAndSmileTestWindow::openCamera()
{
//        qDebug()<<"SAsdaD"<<endl;

    cameraOpen = true;

    getCameraText->setText("关闭摄像头");
    capture = cv::VideoCapture(0);

    contentModeCondition=3;
    cameraTime = new QTimer();
    connect(cameraTime,&QTimer::timeout,this,&faceAndSmileTestWindow::updateCamera);

    cameraTime->start(30);
}

void faceAndSmileTestWindow::closeCamera()
{
//    qDebug()<<"SAD"<<endl;
    cameraTime->stop();
    init();
}
void faceAndSmileTestWindow::updateCamera()
{
    capture >> passFrame;
    if(!passFrame.empty()){
        if(worktrue) emit work_signal();

        QImage ima=QImage(passFrame.data, passFrame.cols, passFrame.rows, QImage::Format_RGB888).rgbSwapped();
        showImage(ima);
    }
}

void faceAndSmileTestWindow::getCameraClicked()
{
    init();
    if(cameraOpen) closeCamera();
    else openCamera();
}


QString faceAndSmileTestWindow::getContentPath(){
    return contentPath;
}


void faceAndSmileTestWindow::faceCheck_set(){
    handleModeCondition = 1;
}
void faceAndSmileTestWindow::smileCheck_set(){
    handleModeCondition = 2;
}

void faceAndSmileTestWindow::work(){

    worktrue = true;

    if(contentModeCondition == 1){
       passFrame = cv::imread(contentPath.toStdString());
       emit work_signal();

       QImage ima=QImage(passFrame.data, passFrame.cols, passFrame.rows, QImage::Format_RGB888).rgbSwapped();
       showImage(ima);
    }
    else if(contentModeCondition == 2){
        cv::VideoCapture video;
        video.open(contentPath.toStdString());

        while (true) {
            video>>passFrame;
            emit work_signal();

            QImage ima=QImage(passFrame.data, passFrame.cols, passFrame.rows, QImage::Format_RGB888).rgbSwapped();
            showImage(ima);
        }

        video.release();
    }
}
