#include "facedatabase.h"
#include <QDebug>
faceDataBase::faceDataBase(QWidget * parent) : QWidget(parent)
{

}

bool faceDataBase::addUserInfo(userInfo user)
{

    for (int i=0,siz=userData.size(); i<siz;i++)
    {
        userInfo now = userData[i];
        if ((now.name==user.name)&&(now.id==user.id)) return false;
    }
    
    userData.push_back(user);
    return true;
}

bool faceDataBase::deleteUserInfo(QString &name_s, QString &id_s)
{
    for (int i=0,siz=userData.size(); i<siz;i++)
    {
        userInfo now = userData[i];
        if ((now.name==name_s)&&(now.id==id_s)) {
            userData.erase(userData.begin()+i);
            return true;
        }
    }
    return false;
}

userInfo faceDataBase::checkUserInfo(QString &name_s, QString &id_s){

    for (int i=0,siz=userData.size(); i<siz;i++)
    {
        userInfo now = userData[i];
        if ((now.name==name_s)&&(now.id==id_s)) return now;
    }
    cv::Mat frame;
    userInfo * user = new userInfo("-1","","","",frame);
    user->name = "-1";
    return *user;
}

std::vector<userInfo> faceDataBase::getAllData(){
    return userData;
}
