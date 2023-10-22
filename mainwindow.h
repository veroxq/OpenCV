#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
//Data
#include <userinfo.h>

//功能
#include <checkhandle.h>
#include <facedatabase.h>

//界面
#include <imageshowwindow.h>
#include <optionbutton.h>
#include <initialwindow.h>
#include <faceandsmiletestwindow.h>
#include <databasewindow.h>
#include <remindwindow.h>
#include <userinfowindow.h>
//布局头文件
#include <QPushButton>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void workStart();
    
private:
    Ui::MainWindow *ui;


    //界面设计
    InitWindow();
    //整体大概布局
    initialWindow * initialwindow;
    faceAndSmileTestWindow * firstWindow;
    dataBaseWindow * secondWindow;


    //左边
    OptionButton * faceCheckButton;
    OptionButton * smileCheckButton;
    OptionButton * humanFaceDataBaseButton;


    //人脸检测
    CheckHandle * checkhandle;

    //笑脸检测
    //数据库管理
    faceDataBase * facedatabase;
    userInfoWindow * userinfoWindow;

};

#endif // MAINWINDOW_H
