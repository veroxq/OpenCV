#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H
#include <cameragetface.h>
#include <userinfo.h>
#include <imageshowwindow.h>
#include <QDialog>
#include <remindwindow.h>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>
#include <opencv2/opencv.hpp>
#include <userinfowindow.h>
class dataBaseWindow: public QWidget
{
     Q_OBJECT
public:
    dataBaseWindow(QWidget * parent = 0);
public:
    QString name;
    QString id;
    QString gender;
    QString age;
    QImage qimage;
    cv::Mat face;

    void init();
    void showTrue();
    void showFalse();
    userInfo getUserInfo();

    bool workcondition;
signals:
    void addUserInfo_signal();
    void deleteUserInfo_signal();
    void checkUserInfo_signal();


private:
    QLabel * backgroundImageLabel;
    QPixmap * backgroundImage;
    bool condition;

    QLineEdit * nameEdit;
    QLineEdit * idEdit;
    QLineEdit * ageEdit;
    QLineEdit * genderEdit;
    QLineEdit * nameEdit_else;
    QLineEdit * idEdit_else;

    QPushButton * uploadImage;
    QPushButton * uploadCamera;
    QPushButton * checkImage;
    
    QPushButton * deleteUserInfoButton;
    QPushButton * addUserInfoButton;
    QPushButton * checkUserInfoButton;

    bool checkAdd();
    bool checkElse();
    void reset();

    //异常

    remindWindow infoLess;
    remindWindow imageEmpty;
    remindWindow faceEmpty;
    remindWindow faceMore;

    remindWindow addSuccess;
    remindWindow addFail;
    remindWindow findFailed;
    remindWindow deleteSuccess;

    //摄像机捕获图像
    cameraGetFace camera;

    //检测
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyesCascade;
    
private slots:

};

#endif // DATABASEWINDOW_H
