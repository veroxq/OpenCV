#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <opencv2/opencv.hpp>
class userInfo
{

public:
    userInfo(QString name_s,QString id_s,QString gender_s,QString age_s,cv::Mat face_s);

    QString name;
    QString id;

    QString gender;
    QString age;

    cv::Mat face;
};

#endif // USERINFO_H
