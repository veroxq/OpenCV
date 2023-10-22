#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QMessageBox>

class Camera :public QObject
{
    Q_OBJECT
public:
    Camera(QObject * parent = 0);
    ~Camera();
public slots:
    void openCamera();
    void closeCamera();

signals:
    void frameCaptured(QImage frame);
    void cameraOpenSuccess();

private:
    cv::VideoCapture cameraObj;

    
};

#endif // CAMERA_H
