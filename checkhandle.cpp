#include "checkhandle.h"
#include <qDebug>
#include <QVBoxLayout>
#include <iostream>
#include <random>

CheckHandle::CheckHandle(QWidget * parent) : QWidget(parent)
{
    //加载人脸检测器
    faceCascade.load("D:/opencv3.4.0/OpenCV-MinGW-Build-OpenCV-3.4.5/etc/haarcascades/haarcascade_frontalface_default.xml");
    smileCascade.load("D:/opencv3.4.0/OpenCV-MinGW-Build-OpenCV-3.4.5/etc/haarcascades/haarcascade_smile.xml");
    eyesCascade.load("D:/opencv3.4.0/OpenCV-MinGW-Build-OpenCV-3.4.5/etc/haarcascades/haarcascade_eye.xml");
}

bool CheckHandle::checkFaceTrue(cv::Mat faceROI)
{
    std::vector<cv::Rect> eyes;
    eyesCascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    // 检测到两个眼睛可认为检测到有效人脸
    if (eyes.size() >= 2)  return true;
    else return false;
}

void CheckHandle::resizeBitmaps(cv::Mat& bitmapA, cv::Mat& bitmapB) {
    cv::Mat resizedBitmapA, resizedBitmapB;

    // 计算缩放因子
    double scale = std::min(static_cast<double>(bitmapA.cols) / bitmapB.cols, static_cast<double>(bitmapA.rows) / bitmapB.rows);

    // 缩放位图
    cv::resize(bitmapA, resizedBitmapA, cv::Size(), scale, scale);
    cv::resize(bitmapB, resizedBitmapB, cv::Size(), scale, scale);

    // 更新原始位图
    bitmapA = resizedBitmapA;
    bitmapB = resizedBitmapB;
}

// 将位图对象转换为灰度矩阵
void CheckHandle::convertToGrayscale(cv::Mat& bitmapA, cv::Mat& bitmapB) {
    cv::cvtColor(bitmapA, bitmapA, cv::COLOR_BGR2GRAY);
    cv::cvtColor(bitmapB, bitmapB, cv::COLOR_BGR2GRAY);
}

// 使用直方图比较灰度矩阵的相似度
double CheckHandle::compareHistogram(const cv::Mat& histA, const cv::Mat& histB) {
    return cv::compareHist(histA, histB, cv::HISTCMP_CORREL);
}

// 使用直方图比较两个位图的相似度
double CheckHandle::compareBitmaps(const cv::Mat& bitmapA, const cv::Mat& bitmapB) {
    // 将位图转换为灰度矩阵
    cv::Mat grayscaleA, grayscaleB;
    cv::cvtColor(bitmapA, grayscaleA, cv::COLOR_BGR2GRAY);
    cv::cvtColor(bitmapB, grayscaleB, cv::COLOR_BGR2GRAY);

    // 计算直方图
    int histSize = 256;
    float range[] = {0, 256};  //像素值范围
    const float* histRange = {range};
    cv::Mat histA, histB;
    cv::calcHist(&grayscaleA,1,0,cv::noArray(),histA, 1, &histSize, &histRange);
    cv::calcHist(&grayscaleB,1,0,cv::noArray(),histB, 1, &histSize, &histRange);
    // 归一化直方图
    cv::normalize(histA, histA, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(histB, histB, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    // 比较直方图
    return compareHistogram(histA, histB);
}
double CheckHandle::faceMatching(cv::Mat bitmapA, cv::Mat bitmapB){
    // 调整尺寸使两个位图宽高保持一致
    resizeBitmaps(bitmapA, bitmapB);

    // 将位图转换为灰度矩阵
    convertToGrayscale(bitmapA, bitmapB);

    // 比较位图
    double similarity = compareBitmaps(bitmapA, bitmapB);
    return similarity;
}
void CheckHandle::match(cv::Mat faceROI,std::vector<userInfo> faceData)
{

    QString str = "no";
    //与数据库匹配
    double similarity = -1;
    //遍历数据库
    for(int j=0,siz=faceData.size();j<siz;++j)
    {
        userInfo userdata = faceData[j];

        //找合法人脸
        std::vector<cv::Rect> dataFaces;
        faceCascade.detectMultiScale(userdata.face,dataFaces,1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE);

        for(int k=0,sizk=dataFaces.size();k<sizk;k++)
        if(checkFaceTrue(userdata.face(dataFaces[k])))
        {
              double nowSimilarity = faceMatching(faceROI,userdata.face(dataFaces[k]));
              //更新数据
              if(nowSimilarity > similarity){
                  str1 = "name: "+userdata.name;
                  str2 = "rate:"+QString::number(nowSimilarity,'f',3);
                  similarity = nowSimilarity;
              }
              break;
          }
    }

    return;
}

cv::Mat CheckHandle::work(cv::Mat frame,const int &handleMode,std::vector<userInfo> dataLine)
{

    std::vector<cv::Rect> faces;
    if(handleMode==1) faceCascade.detectMultiScale(frame,faces,1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE);
    else if(handleMode==2) smileCascade.detectMultiScale(frame,faces, 1.7, 20, 0 | cv::CASCADE_SCALE_IMAGE);

    int x=0;

    for(int i=0,siz=faces.size();i<siz;++i)
    {
        cv::Mat faceROI = frame(faces[i]);

        if(!checkFaceTrue(faceROI)) continue;
        //画出人脸
        cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);


        str1 = "unmatched face";
        str2 = "rate:0.000";
        match(faceROI,dataLine);

        cv::putText(frame,str1.toStdString(), cv::Point(faces[i].x + faces[i].width / 2 - 90, faces[i].y - 70), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        cv::putText(frame,str2.toStdString(), cv::Point(faces[i].x + faces[i].width / 2 - 90, faces[i].y - 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);


    }

      return frame;
}
