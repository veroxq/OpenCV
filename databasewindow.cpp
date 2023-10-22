#include "databasewindow.h"
#include <QDebug>
dataBaseWindow::dataBaseWindow(QWidget *parent) : QWidget(parent)
{
    
    //标记状态
    condition = false;
    faceCascade.load("D:/opencv3.4.0/OpenCV-MinGW-Build-OpenCV-3.4.5/etc/haarcascades/haarcascade_frontalface_default.xml");
    eyesCascade.load("D:/opencv3.4.0/OpenCV-MinGW-Build-OpenCV-3.4.5/etc/haarcascades/haarcascade_eye.xml");

    //各种提示窗口
    infoLess.set("D:/FACE_TEST/image/infoLess.png");
    imageEmpty.set("D:/FACE_TEST/image/picture_close.png");
    faceEmpty.set("D:/FACE_TEST/image/faceEmpty.png");
    faceMore.set("D:/FACE_TEST/image/faceMore.png");

    findFailed.set("D:/FACE_TEST/image/database_findfail.png");
    addSuccess.set("D:/FACE_TEST/image/database_addtrue.png");
    deleteSuccess.set("D:/FACE_TEST/image/dataface_deleteTrue.png");
    addFail.set("D:/FACE_TEST/image/addFailed.png");

    //整体页面
    setFixedSize(2304,1296);
    backgroundImageLabel = new QLabel(this);
    QPixmap backgroundImage("D:/FACE_TEST/image/faceDataWindow.png");
    backgroundImageLabel->setPixmap(backgroundImage.scaled(2304,1296,Qt::KeepAspectRatioByExpanding));
    backgroundImageLabel->setGeometry(0,0,width(),height());


    //Edit部件
    nameEdit = new QLineEdit(this);
    nameEdit->setGeometry(960,470,250,50);
    
    ageEdit = new QLineEdit(this);
    ageEdit->setGeometry(1930,470,100,50);
    
    genderEdit  = new QLineEdit(this);
    genderEdit->setGeometry(1480,470,100,50);
    
    idEdit = new QLineEdit(this);
    idEdit->setGeometry(1065,560,1000,50);

    nameEdit_else = new QLineEdit(this);
    nameEdit_else->setGeometry(960,950,250,50);

    idEdit_else = new QLineEdit(this);
    idEdit_else ->setGeometry(1065,1040,1000,50);

    //得到人脸信息
    uploadImage = new QPushButton(this);
    uploadImage->setGeometry(1100,650,250,50);
    uploadImage->setText("本地上传");

    connect(uploadImage,&QPushButton::clicked,[=](){
        QString Path = QFileDialog::getOpenFileName(this,"选择图片",QString(),"图片文件 (*.png *.jpg *.jpeg)");
        if(!Path.isEmpty()){
            qimage.load(Path);
        }
    });

    uploadCamera = new QPushButton(this);
    uploadCamera->setGeometry(1450,650,250,50);
    uploadCamera->setText("打开摄像头");
    connect(uploadCamera,&QPushButton::clicked,[=](){
        camera.openWindow();
        qimage = camera.getImage();
    });

    checkImage = new QPushButton(this);
    checkImage->setGeometry(1800,650,250,50);
    checkImage->setText("查看图片");
    connect(checkImage,&QPushButton::clicked,[=](){
        if(qimage.isNull()) imageEmpty.exec();
        else{
            imageShowWindow newWindow;
            newWindow.set(qimage);
            newWindow.exec();
        }
    });
    
    //增加删除和查询
    addUserInfoButton = new QPushButton(this);
    addUserInfoButton->setGeometry(1220,730,250,50);
    addUserInfoButton->setText("添加信息");
    connect(addUserInfoButton,&QPushButton::clicked,[=](){
        if(checkAdd()){
            emit addUserInfo_signal();
            if(workcondition){
                addSuccess.exec();
                init();
            }
            else addFail.exec();
        }
    });

    deleteUserInfoButton  = new QPushButton(this);
    deleteUserInfoButton->setGeometry(1030,1150,250,50);
    deleteUserInfoButton->setText("删除信息");

    connect(deleteUserInfoButton,&QPushButton::clicked,[=](){
        if(checkElse()){
            emit deleteUserInfo_signal();
            if(workcondition){
                deleteSuccess.exec();
                init();
            }
            else findFailed.exec();
        }

    });

    checkUserInfoButton = new QPushButton(this);
    checkUserInfoButton->setGeometry(1510,1150,250,50);
    checkUserInfoButton->setText("查询信息");
    connect(checkUserInfoButton,&QPushButton::clicked,[=](){
        if(checkElse()){
            emit checkUserInfo_signal();
        }
    });
    
    this->hide();
}

void dataBaseWindow::init(){
    name = "";
    id = "";
    gender = "";
    age = "";

    nameEdit->clear();
    ageEdit->clear();
    genderEdit->clear();
    idEdit->clear();
    nameEdit_else->clear();
    idEdit_else->clear();
}

bool dataBaseWindow::checkAdd(){

    name = nameEdit->text();
    id = idEdit->text();
    gender = genderEdit->text();
    age = ageEdit->text();

    if(name.isEmpty()||id.isEmpty()||gender.isEmpty()||age.isEmpty()){
        infoLess.exec();
        return false;
    }

    if(qimage.isNull()){
        imageEmpty.exec();
        return false;
    }

    cv::Mat frame(qimage.height(),qimage.width(),CV_8UC4,const_cast<uchar*>(qimage.bits()), qimage.bytesPerLine());
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(frame,faces,1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE);

    int x=0;
    for(int i=0,siz=faces.size();i<siz;++i)
    {
        cv::Mat faceROI = frame(faces[i]);
        std::vector<cv::Rect> eyes;
        eyesCascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // 检测到两个眼睛可认为检测到有效人脸
        if (eyes.size() >= 2) x++;
    }

    if(x==0) {
        faceEmpty.exec();
        return false;
    }
    if(x>1){
        faceMore.exec();
        return false;
    }

    face = frame;
    return true;
}
bool dataBaseWindow::checkElse(){
    name = nameEdit_else->text();
    id = idEdit_else->text();

    if(name.isEmpty()||id.isEmpty()){
        infoLess.exec();
        return false;
    }

    return true;
}

void dataBaseWindow::showTrue()
{
    if(condition) return;
    init();
    condition=true;
    this->show();
}

void dataBaseWindow::showFalse()
{
    if(!condition) return;

    condition=false;
    this->hide();
}

userInfo dataBaseWindow::getUserInfo()
{
    userInfo *user = new userInfo(name,id,gender,age,face);
    return *user;
}
