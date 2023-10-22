#include "userinfo.h"

userInfo::userInfo(QString name_s,QString id_s,QString gender_s,QString age_s,cv::Mat face_s)
{
    name = name_s;
    id = id_s;
    age = age_s;
    gender = gender_s;
    face = face_s;
}
