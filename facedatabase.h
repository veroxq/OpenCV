#ifndef FACEDATABASE_H
#define FACEDATABASE_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QString>
#include <remindwindow.h>
#include <userinfowindow.h>
#include <vector>
#include <userinfo.h>

class faceDataBase : public QWidget
{
    Q_OBJECT
public:
    faceDataBase(QWidget * parent = 0);

    bool addUserInfo(userInfo user);
    bool deleteUserInfo(QString &name_s,QString &id_s);
    userInfo checkUserInfo(QString &name_s,QString &id_s);
    
    std::vector<userInfo> getAllData();
    
private:
    std::vector<userInfo> userData;


    //异常处理窗口

    
};

#endif // FACEDATABASE_H
