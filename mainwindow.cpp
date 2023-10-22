#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QImage>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitWindow();
    
}

MainWindow::InitWindow(){
    //人脸检测初始化
    //笑脸检测初始化
    checkhandle = new CheckHandle(this);


    //数据库
    facedatabase = new faceDataBase(this);

    //设置整体布局
    setFixedSize(2304,1296);

    initialwindow = new initialWindow(this);
    firstWindow = new faceAndSmileTestWindow(this);
    secondWindow = new dataBaseWindow(this);
    userinfoWindow = new userInfoWindow(this);

    initialwindow->show();


    //构建左边选择按钮
    faceCheckButton = new OptionButton(this);
    faceCheckButton->setGeometry(90,330,400,170);//x y 长 宽
    faceCheckButton->setImages("D:/FACE_TEST/image/faceTestButton_false.png","D:/FACE_TEST/image/faceTestButton_true.png");
    faceCheckButton->reset();


    smileCheckButton = new OptionButton(this);
    smileCheckButton->setImages("D:/FACE_TEST/image/smileTestButton_false.png","D:/FACE_TEST/image/smileTestButton_true.png");
    smileCheckButton->setGeometry(90,520,400,170);
    smileCheckButton->reset();

    humanFaceDataBaseButton = new OptionButton(this);
    humanFaceDataBaseButton->setImages("D:/FACE_TEST/image/databaseButton_false.png","D:/FACE_TEST/image/databaseButton_true.png");
    humanFaceDataBaseButton->setGeometry(90,710,400,170);
    humanFaceDataBaseButton->reset();

    connect(faceCheckButton,&OptionButton::clicked,[=](){
        faceCheckButton->set();
        smileCheckButton->reset();
        humanFaceDataBaseButton->reset();

        firstWindow->showTrue();
        firstWindow->faceCheck_set();

        secondWindow->showFalse();

    });
    connect(smileCheckButton,&OptionButton::clicked,[=](){
        faceCheckButton->reset();
        smileCheckButton->set();
        humanFaceDataBaseButton->reset();

        firstWindow->showTrue();
        firstWindow->smileCheck_set();

        secondWindow->showFalse();
    });
    connect(humanFaceDataBaseButton,&OptionButton::clicked,[=](){
        faceCheckButton->reset();
        smileCheckButton->reset();
        humanFaceDataBaseButton->set();

        firstWindow->showFalse();
        secondWindow->showTrue();
    });
    
//    //构建右边页面

    //关联开始检测按钮
    connect(firstWindow,&faceAndSmileTestWindow::work_signal,this,&MainWindow::workStart);

    //关联图片更新功能


    //添加删除查找
    connect(secondWindow,&dataBaseWindow::addUserInfo_signal,[=](){
        secondWindow->workcondition=facedatabase->addUserInfo(secondWindow->getUserInfo());
    });

    connect(secondWindow,&dataBaseWindow::deleteUserInfo_signal,[=](){
        secondWindow->workcondition=facedatabase->deleteUserInfo(secondWindow->name,secondWindow->id);
    });
    connect(secondWindow,&dataBaseWindow::checkUserInfo_signal,[=](){
        userInfo user=facedatabase->checkUserInfo(secondWindow->name,secondWindow->id);
        if(user.name=="-1"){
            remindWindow findFailed;
            findFailed.set("D:/FACE_TEST/image/database_findfail.png");
            findFailed.exec();
        }
        else{
            secondWindow->init();
            userinfoWindow->set(user);
        }
    });


}

void MainWindow::workStart(){
    firstWindow->passFrame = checkhandle->work(firstWindow->passFrame,firstWindow->handleModeCondition,facedatabase->getAllData());
}

MainWindow::~MainWindow()
{
    delete ui;
}
