#ifndef CHECKHANDLE_H
#define CHECKHANDLE_H

#include <QImage>
#include <QTimer>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <remindwindow.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <userinfo.h>

class CheckHandle : public QWidget
{
    Q_OBJECT
public:
    CheckHandle(QWidget * parent = 0);
public:
    cv::Mat work(cv::Mat frame,const int &handleMode,std::vector<userInfo> dataLine);

private:
    //检测级联分类器
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyesCascade;
    cv::CascadeClassifier smileCascade;

    void resizeBitmaps(cv::Mat &bitmapA, cv::Mat &bitmapB);
    void convertToGrayscale(cv::Mat &bitmapA, cv::Mat &bitmapB);
    double compareHistogram(const cv::Mat &histA, const cv::Mat &histB);
    double compareBitmaps(const cv::Mat &bitmapA, const cv::Mat &bitmapB);
    double faceMatching(cv::Mat bitmapA, cv::Mat bitmapB);


    bool checkFaceTrue(cv::Mat faceROI);
    void match(cv::Mat faceROI,std::vector<userInfo> faceData);
    QString str1,str2;
};

#endif // CHECKHANDLE_H
